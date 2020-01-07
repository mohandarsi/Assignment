// Timer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Timer.h"
#include<iostream>
#include <iomanip>
class MyTask : public TimerTask
{
public: 
	MyTask():TimerTask("MyTask"){}
	virtual void Run()
	{
		std::time_t t = std::time(nullptr);
		std::cout << "RUN Executed" << t;
	}
};

int main()
{
	unique_ptr<Timer> timer(new Timer());

	shared_ptr<TimerTask> task(new MyTask());
	
	timer->Schedule(task, std::chrono::duration_cast<std::chrono::nanoseconds>(chrono::minutes(1)));

	timer->Schedule(task, std::chrono::duration_cast<std::chrono::nanoseconds>(chrono::minutes(2)));
	
	std::this_thread::sleep_for(60s);

	timer->Schedule(task, std::chrono::duration_cast<std::chrono::nanoseconds>(chrono::minutes(1)));

	std::this_thread::sleep_for(80s);

	timer->Stop();
	timer.reset();
    return 0;
}

