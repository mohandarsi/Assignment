#include "stdafx.h"
#include "Timer.h"
using namespace chrono;

Timer::Timer()
{
	m_TimerThread = thread([this] { Run(); });
}

Timer::~Timer()
{
	if (!m_bDestroy)
		Stop();
}

void Timer::Stop()
{
	{
		std::unique_lock<mutex>  lock(m_mutex);
		m_bDestroy = true;
		cv.notify_all();
		m_taskTable.clear();
	}
	m_TimerThread.detach();

}

void Timer::Schedule(const TimerTask::TimerTaskPtr task, chrono::nanoseconds delay)
{
	
	std::unique_lock<mutex>  lock(m_mutex);
    auto now =    high_resolution_clock::now().time_since_epoch();
	auto schtime = now.count() + delay.count();
	if (schtime < now.count())
	{
		throw exception("invalid delay time");
	}
	TimerTaskDelay::TimerTaskDelayPtr newItem(new Timer::TimerTaskDelay(now, delay, task));
	m_taskTable.insert(newItem);
	cv.notify_one();

}
void Timer::Cancel(const TimerTask::TimerTaskPtr task)
{
	std::unique_lock<mutex>  lock(m_mutex);

	for (auto it = m_taskTable.begin(); it != m_taskTable.end(); it++) {
		if ((*it)->m_Task == task)
		{
			m_taskTable.erase(it);
			break;
		}
	}
}
void
Timer::runTask(const TimerTask::TimerTaskPtr& task)
{
	task->Run();
}
void Timer::Run()
{
	std::cout << "Timer:Run Enter";
	while (!m_bDestroy)
	{
		shared_ptr<Timer::TimerTaskDelay> delayTask;
		{ // for unique lock
			std::unique_lock<mutex> lock(m_mutex);
			if (m_taskTable.empty())
			{
				cv.wait(lock, [&] {return m_taskTable.empty(); });
			}
			while (m_taskTable.empty() == false)
			{
				auto first = *(m_taskTable.begin());
				auto now = high_resolution_clock::now().time_since_epoch();
				try
				{
					//if time not reached wait for it
					cv.wait_for(lock, first->GetExecutionTime() - now);
				}
				catch (const exception& e)
				{
					//log or dispaly error // do necessary actions??
				}
				if (first->GetExecutionTime() <= now && !m_bDestroy)
				{
					delayTask = first;
					m_taskTable.erase(first);
					break;
				}
			}
		}
		if (!m_bDestroy && delayTask != nullptr && delayTask->m_Task)
		{
			try
			{
				//execute the task;
				runTask(delayTask->m_Task);
			}
			catch (const exception& e)
			{
				//log or dispaly error
			}
		}
		
	}
	std::cout << "Timer:Run Exit";

}

inline
Timer::TimerTaskDelay::TimerTaskDelay(const chrono::nanoseconds &scheduledTime,
	const chrono::nanoseconds &delay, const TimerTask::TimerTaskPtr& taskPtr) :
	m_ScheduledTime(scheduledTime), m_Delay(delay), m_Task(taskPtr)
{

}
inline chrono::nanoseconds Timer::TimerTaskDelay::GetExecutionTime() const
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