#pragma once
#include<memory>
#include<set>
#include<thread>
#include<mutex>
#include<chrono>
#include <ctime>

class TimerTask;
class Timer
{
public:
    Timer();
    void Schedule(const std::shared_ptr<TimerTask> &task, std::chrono::nanoseconds delay);
    std::shared_ptr<TimerTask> Schedule(const std::function<void()> &command, std::chrono::nanoseconds delay);
    void Wait();
    void Cancel(const std::shared_ptr<TimerTask> task);
    void Stop();
    virtual ~Timer();
private:
    struct TimerTaskDelay
    {
        std::weak_ptr<TimerTask> m_Task;
        std::chrono::nanoseconds m_ScheduledTime;
        std::chrono::nanoseconds m_Delay;
        inline TimerTaskDelay(const std::chrono::nanoseconds &scheduledTime, const std::chrono::nanoseconds &delay, const std::shared_ptr<TimerTask>&);
        inline bool operator<(const TimerTaskDelay& dealy) const;
        inline std::chrono::nanoseconds GetExecutionTime() const;
    };

    bool m_bDestroy = false;
    std::set<std::shared_ptr<TimerTaskDelay>> m_taskTable;
    std::thread m_TimerThread;
    std::mutex m_mutex;
    std::condition_variable m_taskAvailable;
    void run();
    void runTask(const std::shared_ptr<TimerTask>& task);
    
    
};


