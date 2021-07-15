#include "Interface.h"

Interface::Interface()
{
	std::cout << "Interface created" << std::endl;

}

Interface::~Interface()
{
	std::cout << "Interface deleted" << std::endl;

}

void Interface::Initialize()
{
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(m_settings.GetWindowDimensions().x, m_settings.GetWindowDimensions().y), RandomString(26), sf::Style::Default);
	ImGui::SFML::Init(*m_window);

	m_injector.Initialize();

	WriteToConsole("Welcome to the CSGO DLL Injector!");
	WriteToConsole("Hopefully the slide and shit is working");
}

void Interface::Destroy() {
	m_injector.Destroy();
}

void Interface::Run() {

	m_settings.SetFrameRate(60);
	auto targetTime = m_settings.GetTargetTime();
	sf::Clock deltaClock;
	while (m_window->isOpen()) {
		auto startTime = std::chrono::high_resolution_clock::now();
		HandleEvents();
		Update(dt, deltaClock.restart());
		Draw();
		auto endTime = std::chrono::high_resolution_clock::now();
		auto deltaTime = startTime - endTime;

		if (deltaTime < targetTime) {
			auto remainingTime = targetTime - deltaTime - std::chrono::milliseconds(5);
			if (remainingTime > std::chrono::milliseconds(0)) {
				std::this_thread::sleep_for(remainingTime);

				while ((std::chrono::high_resolution_clock::now() - startTime) < targetTime) {}
			}
		}
		dt = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - startTime).count();
		//std::cout << dt << std::endl;
	}
}

void Interface::HandleEvents() {

	sf::Event event;

	while (m_window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			m_window->close();
			Destroy();
			break;
		case sf::Event::Resized:
			break;
		case sf::Event::KeyPressed:
			m_inputState.CheckKeyboardInputs();
		case sf::Event::KeyReleased:
			m_inputState.CheckKeyboardInputs();
		case sf::Event::MouseButtonPressed:
			m_inputState.CheckMouseInputs();
		case sf::Event::MouseButtonReleased:
			m_inputState.CheckMouseInputs();
		}
		ImGui::SFML::ProcessEvent(event);
	}
}

void Interface::Update(double in_dt, sf::Time in_time)
{
	ImGui::SFML::Update(*m_window, in_time);

	//m_injector.Update(in_dt);
}

void Interface::Draw()
{
	float width = m_settings.GetWindowDimensions().x;
	float height = m_settings.GetWindowDimensions().y;
	float buffer = 15.0f;

	bool isOpen = false;

	// ImGui
	ImGui::Begin("Inject Custom DLL", &isOpen);
	ImGui::SetWindowSize({ width, height });

	// Inject DLL
	if (ImGui::Button("Inject DLL")) {
		if (m_injector.InjectDLL()) { WriteToConsole("DLL Succesfully Injected!", ImVec4(0, 1, 0, 1)); }
		else { WriteToConsole("DLL Injection Failed :(", ImVec4(1, 0, 0, 1)); }
	}

	if (ImGui::Button("Add DLL")) {
		if (m_injector.SetDLL(m_inputDLLPath)) { WriteToConsole("DLL Succesfully Set", ImVec4(0, 1, 0, 1)); }
		else { WriteToConsole("Could not find specified DLL", ImVec4(1, 0, 0, 1)); }
	}
	ImGui::SameLine();
	ImGui::InputText("", m_inputDLLPath, sizeof(m_inputDLLPath));

	// Output console
	ImGui::TextColored(ImVec4{ 0, 1, 0, 1 }, "Output Console:");
	ImGui::BeginChild("Scrolling", ImVec2(width - buffer, 0), true);
	for (unsigned int i = 0; i < m_consoleOutputs.size(); i++) {
		ImGui::TextColored(m_consoleOutputs[i].second, m_consoleOutputs[i].first, i);
	}
	ImGui::EndChild();

	ImGui::End();

	// Render
	m_window->clear(sf::Color::Black);

	ImGui::SFML::Render(*m_window);

	m_window->display();
}

void Interface::WriteToConsole(const char* text, const ImVec4& color) {
	m_consoleOutputs.emplace_back(text, color);
}

// ////////////////////Input Class///////////////////
void Input::ClearKeyboardInputs() {

	keyUpPressed = false;
	keyLeftPressed = false;
	keyDownPressed = false;
	keyRightPressed = false;
	keySpacePressed = false;
}

void Input::CheckKeyboardInputs() {

	ClearKeyboardInputs();

	keyUpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	keyLeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	keyDownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	keyRightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	keySpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

void Input::ClearMouseInputs() {

	mouseLeftPressed = false;
	mouseRightPressed = false;
}

void Input::CheckMouseInputs() {
	ClearMouseInputs();

	mouseRightPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	mouseLeftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}