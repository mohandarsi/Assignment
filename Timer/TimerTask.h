#pragma once
#include "Interfaces.h"
using namespace std;
class TimerTask
{
public:
	typedef shared_ptr<TimerTask> TimerTaskPtr;
	TimerTask(const string &name);
	virtual void Run() PURE;
	string GetName() { return m_Name; }
	~TimerTask();
private:
	string m_Name;
};

