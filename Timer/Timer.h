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
    void Schedule(const std::shared_ptr<TimerTask> &task, std::chrono::high_resolution_clock::duration delay);
    std::shared_ptr<TimerTask> Schedule(const std::function<void()> &&command, std::chrono::high_resolution_clock::duration delay);
    void Wait();
    void Cancel(const std::shared_ptr<TimerTask> task);
    void Stop();
    virtual ~Timer();
private:
    struct TimerTaskDelay
    {
        std::weak_ptr<TimerTask> m_Task;
        std::chrono::high_resolution_clock::time_point m_ScheduledTime;
        std::chrono::high_resolution_clock::duration m_Delay;
        inline TimerTaskDelay(std::chrono::high_resolution_clock::time_point scheduledTime, std::chrono::high_resolution_clock::duration delay, const std::shared_ptr<TimerTask>&);
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


