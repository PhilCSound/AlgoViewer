
#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "TGUI/TGUI.hpp"
#include "State.hpp"
#include <vector>

class State;

class Application
{
public:
	Application();
	~Application();
	const bool IsRunning() const;
	void Update();
	void ChangeState(State* state);
	void PushState(State* state);
	void PopState();

	sf::RenderWindow& GetWindow() { return m_window; }

private:
	void HandleInput();

	std::vector<State*> m_stackOfStates;
	std::vector<short> m_data;

	sf::Clock m_clock;
	bool m_isRunning;
	sf::RenderWindow m_window;
	tgui::GuiSFML m_gui;
};