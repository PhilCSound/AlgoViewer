
#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "TGUI/TGUI.hpp"
#include <vector>

class Application
{
public:
	Application();
	~Application();
	const bool IsRunning() const;
	void Update();

	sf::RenderWindow& GetWindow() { return m_window; }

private:
	void HandleInput();

	sf::Clock m_clock;
	bool m_isRunning;
	sf::RenderWindow m_window;
	tgui::GuiSFML m_gui;
};