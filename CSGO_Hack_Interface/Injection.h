#pragma once

#include "WindowsHelper.h"
#include "Offsets.h"

class Injector {
public:
	Injector();
	~Injector();

	void Initialize();
	void Destroy();
	
	bool InjectDLL();

	bool SetDLL(const char* DLLPath);
	bool SetProcess(const char* processName);
	bool ChangeProcess(const char* processName);

private:
	const char* m_DLLPath;
	DWORD m_dwProcessID;
	HANDLE m_hGameProcess;
	uintptr_t m_moduleBase;
};