#pragma once
#include "../Core/globals.h"
#include <Windows.h>

class cMemoryManager
{
public:
	cMemoryManager();
	~cMemoryManager();

	template <class cData>
	cData Read(uintptr_t dwAddress)
	{
		cData cRead;
		ReadProcessMemory(GLOBAL_DEFINITION::memoryProcess, (LPVOID)dwAddress, &cRead, sizeof(cData), NULL);
		return cRead;
	}

	template <class cData>
	void Write(uintptr_t dwAddress, cData write)
	{
		WriteProcessMemory(GLOBAL_DEFINITION::memoryProcess, (LPVOID)dwAddress, &write, sizeof(cData), NULL);
	}

	virtual HANDLE  setProcess(const char* ProcessName);
	virtual uintptr_t baseModuleAddress(const char* ModuleName);
	virtual uintptr_t baseModuleSize(const char* ModuleName);
	virtual bool  DataCompare(BYTE* data, BYTE* sign, char* mask);
	virtual uintptr_t FindSignature(uintptr_t base, uintptr_t size, BYTE* sign, char* mask);
};

extern cMemoryManager* MemoryManager;
