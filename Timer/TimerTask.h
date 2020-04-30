#pragma once
#include "Interfaces.h"

class TimerTask
{
public:
	TimerTask(const std::string &name);
	virtual void Run() PURE;
    std::string GetName() { return m_Name; }
	virtual ~TimerTask();
private:
    std::string m_Name;
};

