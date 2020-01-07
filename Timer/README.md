# Timer
To schedule tasks and run in future at specified time 
Timer class manages execution of scheduled tasks.
Uses C++11 features.
Provides interfaces for schedule an task in future time(uses chrono nanoseconds).

To execute task client should create new class derived from TimerTask and has to implement Run method.
```
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

unique_ptr<Timer> timer(new Timer());

shared_ptr<TimerTask> task(new MyTask());
	
// task will be run after 1 min.
timer->Schedule(task, std::chrono::duration_cast<std::chrono::nanoseconds>(chrono::minutes(1)));

//  can be stop the processing
timer->Stop();
	
```
