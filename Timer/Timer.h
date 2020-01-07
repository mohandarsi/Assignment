#pragma once
#include<memory>
#include<set>
#include<thread>
#include<mutex>
#include<chrono>
#include <ctime>
#include "TimerTask.h"

class Timer
{
public:
	Timer();
	void Schedule(const TimerTask::TimerTaskPtr task, chrono::nanoseconds delay);
	void Cancel(const TimerTask::TimerTaskPtr task);
	void Stop();
	virtual ~Timer();
private:
	struct TimerTaskDelay
	{
		typedef shared_ptr<TimerTaskDelay> TimerTaskDelayPtr;
		TimerTask::TimerTaskPtr m_Task;
		chrono::nanoseconds m_ScheduledTime;
		chrono::nanoseconds m_Delay;
		inline TimerTaskDelay(const chrono::nanoseconds &scheduledTime, const chrono::nanoseconds &delay, const TimerTask::TimerTaskPtr&);
		inline bool operator<(const TimerTaskDelay& dealy) const;
		inline chrono::nanoseconds GetExecutionTime() const;
	};

	bool m_bDestroy = false;
	set<TimerTaskDelay::TimerTaskDelayPtr> m_taskTable;
	thread m_TimerThread;
	mutex m_mutex;
	std::condition_variable cv;
	void Run();
	void runTask(const TimerTask::TimerTaskPtr& task);
	
	
};


