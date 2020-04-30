// Timer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>
#include <iomanip>
#include<thread>
#include <chrono>

#include "Timer.h"
#include "TimerTask.h"

class MyTask : public TimerTask
{
public: 
    MyTask():TimerTask("MyTask"){}
    virtual void Run()
    {
        std::cout << "MyTask Executed :"<< this->GetName().c_str() << " time: " << std::chrono::steady_clock::now().time_since_epoch().count() <<std::endl;
    }
};

int main()
{
    using namespace std::chrono_literals;

    std::unique_ptr<Timer> timer(std::make_unique<Timer>());

    auto commandTask = 
        timer->Schedule(
            [](){std::cout << "my command  2+5 ="  << 2+5 << " time:" << std::chrono::steady_clock::now().time_since_epoch().count() << std::endl; },
            std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(4)));


    std::shared_ptr<TimerTask> task(std::make_shared<MyTask>());
        
    timer->Schedule(task, std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(5)));

    timer->Schedule(task, std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::minutes(2)));

    timer->Schedule(task, std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::minutes(1)));

    timer->Wait();

    std::this_thread::sleep_for(2s);

    timer->Stop();
    timer.reset();
    return 0;
}

