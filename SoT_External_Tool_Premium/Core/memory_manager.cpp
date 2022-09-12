#include "memory_manager.h"
#include <TlHelp32.h>

cMemoryManager* MemoryManager = new cMemoryManager();

cMemoryManager::cMemoryManager()
{
}

cMemoryManager::~cMemoryManager()
{
	CloseHandle(GLOBAL_DEFINITION::memoryProcess);
}

HANDLE cMemoryManager::setProcess(const char* ProcessName)
{
	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 ProcEntry;
	ProcEntry.dwSize = sizeof(ProcEntry);

	do
		if (!strcmp(ProcEntry.szExeFile, ProcessName))
		{
			GLOBAL_DEFINITION::memoryProcessID = ProcEntry.th32ProcessID;
			CloseHandle(hPID);

			return GLOBAL_DEFINITION::memoryProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GLOBAL_DEFINITION::memoryProcessID);

		}
	while (Process32Next(hPID, &ProcEntry));

}

bool cMemoryManager::DataCompare(BYTE* data, BYTE* sign, char* mask)
{
	for (; *mask; mask++, sign++, data++)
	{
		if (*mask == 'x' && *data != *sign)
		{
			return false;
		}
	}
	return true;
}

uintptr_t cMemoryManager::FindSignature(uintptr_t base, uintptr_t size, BYTE* sign, char* mask)
{
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	uintptr_t offset = 0;
	while (offset < size)
	{
		VirtualQueryEx(GLOBAL_DEFINITION::memoryProcess, (LPCVOID)(base + offset), &mbi, sizeof(MEMORY_BASIC_INFORMATION));
		if (mbi.State != MEM_FREE)
		{
			BYTE* buffer = new BYTE[mbi.RegionSize];
			ReadProcessMemory(GLOBAL_DEFINITION::memoryProcess, mbi.BaseAddress, buffer, mbi.RegionSize, NULL);
			for (int i = 0; i < mbi.RegionSize; i++)
			{
				if (DataCompare(buffer + i, sign, mask))
				{
					delete[] buffer;
					return (uintptr_t)mbi.BaseAddress + i;
				}
			}

			delete[] buffer;
		}
		offset += mbi.RegionSize;
	}
	return 0;
}

uintptr_t cMemoryManager::baseModuleAddress(const char* ModuleName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, GLOBAL_DEFINITION::memoryProcessID);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!strcmp(modEntry.szModule, ModuleName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

uintptr_t cMemoryManager::baseModuleSize(const char* ModuleName)
{
	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GLOBAL_DEFINITION::memoryProcessID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);

	do
		if (!strcmp(mEntry.szModule, ModuleName))
		{
			CloseHandle(hModule);
			return (uintptr_t)mEntry.modBaseSize;
		}
	while (Module32Next(hModule, &mEntry));

	return 0;
}
