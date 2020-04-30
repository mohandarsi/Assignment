#include "stdafx.h"
#include "Timer.h"
#include "TimerTask.h"


class FunTimerTask : public TimerTask
{
public:
    FunTimerTask(const std::string &name, const std::function<void()> &command) : TimerTask(name), m_command(command){};
    void Run() override
    {
        m_command();
    }
    ~FunTimerTask()
    {
        std::cout << "~FunTimerTask" << std::endl;
    }
private:
    std::function<void()> m_command;
};


Timer::Timer()
{
    m_TimerThread = std::thread([this] { run(); });
}

Timer::~Timer()
{
    if (!m_bDestroy)
        Stop();
}

void Timer::Stop()
{
    {
        std::unique_lock<std::mutex>  lock(m_mutex);
        m_bDestroy = true;
        m_taskAvailable.notify_all();
        m_taskTable.clear();
    }
    m_TimerThread.detach();

}

void Timer::Schedule(const std::shared_ptr<TimerTask> &task, std::chrono::nanoseconds delay)
{
    
    std::unique_lock<std::mutex>  lock(m_mutex);
    auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto schtime = now.count() + delay.count();
    if (schtime < now.count())
    {
        throw std::exception("invalid delay time");
    }
    std::shared_ptr<TimerTaskDelay> newItem(std::make_shared<TimerTaskDelay>(now, delay, task));
    m_taskTable.insert(newItem);
    m_taskAvailable.notify_one();
}

std::shared_ptr<TimerTask>  Timer::Schedule(const std::function<void()> &command, std::chrono::nanoseconds delay)
{
    std::shared_ptr<FunTimerTask> task(std::make_shared<FunTimerTask>("commandTask",command));
    Schedule(task, delay);
    return task;
}

void Timer::Cancel(const std::shared_ptr<TimerTask> task)
{
    std::unique_lock<std::mutex>  lock(m_mutex);

    for (auto it = m_taskTable.begin(); it != m_taskTable.end(); it++) {
        if ((*it)->m_Task.lock() == task)
        {
            m_taskTable.erase(it);
            break;
        }
    }
}
void
Timer::runTask(const std::shared_ptr<TimerTask>& task)
{
    task->Run();
}
void
Timer::Wait()
{
    using namespace std::chrono_literals;
    while (!m_taskTable.empty())  std::this_thread::sleep_for(2s);
    
}
void Timer::run()
{
    std::cout << "Timer:Run Enter" <<std::endl;
    while (!m_bDestroy)
    {
        std::shared_ptr<Timer::TimerTaskDelay> delayTask;
        { // for unique lock
            std::unique_lock<std::mutex> lock(m_mutex);
            if (m_taskTable.empty())
            {
                m_taskAvailable.wait(lock, [&] {return m_taskTable.empty(); });
            }
            while (m_taskTable.empty() == false)
            {
                auto first = *(m_taskTable.begin());
                auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
                try
                {
                    //if time not reached wait for it
                    m_taskAvailable.wait_for(lock, first->GetExecutionTime() - now);
                }
                catch (const std::exception& e)
                {
                    //log or dispaly error // do necessary actions??
                    std::cout << "Exception:" << e.what();
                }
                if (first->GetExecutionTime() <= now && !m_bDestroy)
                {
                    delayTask = first;
                    m_taskTable.erase(first);
                    break;
                }
            }
        }

       
        if (!m_bDestroy && delayTask != nullptr )
        {
            try
            {
                auto timerTask = delayTask->m_Task.lock();
                if (timerTask == nullptr)
                {
                    std::cout << "Invlaid task :" << delayTask << std::endl;
                    m_taskTable.erase(delayTask);
                }
                else
                {
                    //execute the task;
                    runTask(timerTask);
                }
            }
            catch (const std::exception& e)
            {
                //log or dispaly error
                std::cout << "Exception:" << e.what();
            }
        }
        
    }
    std::cout << "Timer:Run Exit";

}

inline
Timer::TimerTaskDelay::TimerTaskDelay(const std::chrono::nanoseconds &scheduledTime,
    const std::chrono::nanoseconds &delay, const std::shared_ptr<TimerTask>& taskPtr) :
    m_ScheduledTime(scheduledTime), m_Delay(delay), m_Task(taskPtr)
{

}
inline std::chrono::nanoseconds Timer::TimerTaskDelay::GetExecutionTime() const
{
    return m_ScheduledTime + m_Delay;
}

inline bool
Timer::TimerTaskDelay::operator<(const TimerTaskDelay& dealy) const
{
    if (m_ScheduledTime < dealy.m_ScheduledTime)
    {
        return true;
    }
    return false;
}