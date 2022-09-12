#include "../Core/globals.h"

namespace GLOBAL_DEFINITION
{
	int rWidth = 0;
	int rHeight = 0;

	int PMrWidth = 0;
	int PMrHeight = 0;

	HWND tWnd = 0x0;
	HWND hWnd = 0x0;
	HWND hMsg = 0x0;

	D3DXMATRIX vMatrix;

	HANDLE hGame = 0x0;
	DWORD dwBase = 0x0;

	bool MenuShown = false;
	int FramesPerSecond = 0;

	DWORD baseThreadID;

	DWORD baseProcessID;
	uintptr_t memoryProcessID;
	HANDLE memoryProcess;

	uintptr_t baseModule;
	uintptr_t baseModuleSize;
	uintptr_t UWorld;
	uintptr_t GNames;
	uintptr_t GObjects;
};

namespace ThreadsManager
{
	DWORD hOverlayRefreshID;
	DWORD hOverlayPositionID;
	DWORD hDataShareID;
	DWORD hDebugDataShareID;
};
