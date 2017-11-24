========================================================================
    CONSOLE APPLICATION : Timer Project Overview
========================================================================

Timer class manages execution of scheduled tasks.
Uses C++11 features.
Provides interfaces for schedule an task in future time(uses chrono nanoseconds).

To execute task client should create new class derived from TimerTask and has to implement Run method.
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

Scheduled Tasks get executed sequentially.

TODO:Need to implement functionality for Repeatative task




This file contains a summary of what you will find in each of the files that
make up your Timer application.


Timer.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Timer.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Main.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Timer.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
