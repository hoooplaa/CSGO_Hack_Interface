#include "Injector.h"

Injector::Injector() {

}

Injector::~Injector() {

}

void Injector::Initialize() {
	SetProcess("csgo.exe");
	SetDLL("DLL\\cheat.dll");
}

void Injector::Destroy() {

}

bool Injector::InjectDLL() {
	if (Proc::InjectDLL(m_dwProcessID, m_hGameProcess, m_DLLPath)) { return true; }
	else { return false; }
}

bool Injector::SetDLL(const char* DLLPath) {
	if (!DoesFileExist(DLLPath)) {
		std::cout << "Could not find DLL at specified path" << std::endl;
		return false;
	}

	m_DLLPath = DLLPath;
	std::cout << "DLL added" << std::endl;

	return true;
}

bool Injector::SetProcess(const char* processName) {
	m_dwProcessID = Proc::GetProcessId("csgo.exe");
	if (!m_dwProcessID) {
		std::cout << "Could not find CSGO process :(" << std::endl;
		return false;
	}

	m_hGameProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_dwProcessID);
	if (!m_hGameProcess) {
		std::cout << "Could not open CSGO process :(" << std::endl;
		return false;
	}

	m_moduleBase = Proc::GetModuleBaseAddress(m_dwProcessID, "client.dll");

	return true;
}