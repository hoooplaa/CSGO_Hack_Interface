#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

#include <time.h>
#include <comdef.h> // For _bstr_t: to convert WCHAR* to type compatable with const char*


void Cleanup(const char* message);
void ThrowLastError(const char* message);
std::string RandomString(const size_t length);
bool DoesFileExist(const char* name);

template<typename T> T ReadProcessMemory_T(const HANDLE processHandle, const size_t address);
template<typename T> T WriteProcessMemory_T(const HANDLE processHandle, const size_t address, T buffer);

namespace Proc {
	DWORD GetProcessId(const char* ProcessName);
	uintptr_t GetModuleBaseAddress(const DWORD pid, const char* modName);

	bool InjectDLL(const DWORD ProcessID, const HANDLE gameHandle, const std::string& dllPath);
	bool LoadLibraryInject(const DWORD ProcessId, const char* Dll);
}

namespace Internal {
	bool ExecuteBypass(HANDLE hProcess);
	bool Backup(HANDLE hProcess);
}


