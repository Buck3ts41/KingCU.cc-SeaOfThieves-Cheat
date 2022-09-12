#pragma once
#include "../Core/memory_manager.h"
#include <string>

class cProcessManager
{
public:
	int Size[2];
	int Position[2];
	HWND myWindow;
	bool zoomOnce = false;
public:
	bool attachProcess(std::string Process);
	bool setWindow(std::string Window);
	bool isWindowActive();
	bool getSize();
	bool isWindowMaximized();
private:
	RECT WindowRect;
	RECT frame;
	HWND targetWindow;
	HANDLE targetProcess;
};

extern cProcessManager* ProcessManager;