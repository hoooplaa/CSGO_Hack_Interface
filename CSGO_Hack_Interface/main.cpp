// =============================== CSGO DLL Injector =========================== //
//
// CREDIT: ImGui DLL injector interface. DLL bypass based on youtube tutorial "Undetected LoadLibrary DLL Injector
//		   Tutorial (CSGO)" given by Cyborg Elf. - https://www.youtube.com/watch?v=mQZhLEgvpnA
//
// ===================================== NOTES ================================== //
//
// Make sure to compile in x86 using Mulitbyte character set
//
// _CRT_SECURE_NO_WARNINGS is turned on
//
// IDEAS:
//      1. Make a dropdown memu that contains all the available processes
//
//      2. Think of better way to handle errors
//

#include "Interface.h"

const std::string DLL_PATH = "DLL/cheats.dll";

int main() {
	SetConsoleTitleA(RandomString(26).c_str()); // Some anticheats can detetct console titles

	std::shared_ptr<Interface> csgoInjector = std::make_shared<Interface>();

	csgoInjector->Initialize();
	csgoInjector->Run();

	Cleanup("Code ran successfully! :)");
}