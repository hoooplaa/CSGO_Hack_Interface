#pragma once

#include "../WindowsHelper/WindowsHelper.h"
#include "../CSGO/Offsets.h"

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

	const char* GetDLLPath() const { return m_DLLPath; }

private:
	const char* m_DLLPath = "C:\\Users\\Alex Haurin\\source\\repos\\CSGO_Hack_Interface\\DLL\\cheat.dll";
	DWORD m_dwProcessID{};
	HANDLE m_hGameProcess{};
	uintptr_t m_moduleBase{};
};