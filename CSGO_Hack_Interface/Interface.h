#pragma once

#include <chrono>
#include <thread>

#include "SFML/Graphics.hpp"
#include "ImGui/imgui.h"
#include "Imgui-SFML/imgui-SFML.h"

#include "Injection.h"

class Input {
public:
	void ClearKeyboardInputs();
	void CheckKeyboardInputs();

	void ClearMouseInputs();
	void CheckMouseInputs();

	bool keyRightPressed = false;
	bool keyLeftPressed = false;
	bool keyUpPressed = false;
	bool keyDownPressed = false;
	bool keySpacePressed = false;

	bool mouseLeftPressed = false;
	bool mouseRightPressed = false;
};

class InterfaceSettings {
public:
	using tVector  = sf::Vector2f;
	using tVectorU = sf::Vector2u;
	using tColor   = sf::Color;
	using tString  = sf::String;

	double GetFrameRate() const { return m_frameRate; }
	void   SetFrameRate(double in_frameRate) {
		m_frameRate = in_frameRate;
		m_targetTime = std::chrono::milliseconds(1000 / (int)in_frameRate);
	}

	std::chrono::milliseconds GetTargetTime() const { return m_targetTime; }
	void SetTargetTime(std::chrono::milliseconds in_targetTime) { m_targetTime = in_targetTime; }

	tVectorU GetWindowDimensions() const { return m_windowDimensions; }
	void    SetWindowDimensions(tVectorU& in_dimensions) { m_windowDimensions = in_dimensions; }

	tString GetWindowTitle() const { return m_windowTitle; }
	void    SetWindowTitle(tString& in_title) { m_windowTitle = in_title; }

private:
	double  m_frameRate = 120.0;
	std::chrono::milliseconds m_targetTime;

	tString m_windowTitle = "Lets Hack Some CSGO BOIIIIIIIIIIIIII";
	tVectorU m_windowDimensions = { 1200, 800 };
};

class Interface {
public:
	Interface();
	~Interface();
	void Initialize();
	void Destroy();

	void Run();
	void HandleEvents();
	void Update(double in_dt, sf::Time in_time);
	void Draw();

	void WriteToConsole(const char* text, const ImVec4& color = { 1, 1, 1, 1 });

	InterfaceSettings GetSettings() const { return m_settings; }

private:
	double dt = 1.0;
	
	// General
	InterfaceSettings m_settings;
	Input m_inputState;

	// ImGui
	std::vector<std::pair<const char*, ImVec4>> m_consoleOutputs;
	char m_inputDLLPath[1048] = "DLL\\cheat.dll";

	// Injector
	Injector m_injector;

	std::shared_ptr<sf::RenderWindow> m_window;
	float m_aspectRatio = 1.0f;
};