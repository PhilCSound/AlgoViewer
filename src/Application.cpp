#include "Application.hpp"

Application::Application()
{
	m_window.create(sf::VideoMode(800, 600, 32), "PokeClone");
	m_window.setFramerateLimit(60);
	m_window.setVerticalSyncEnabled(false);
	m_isRunning = m_window.isOpen();
	m_gui.setTarget(m_window);
}


Application::~Application()
{
}

const bool Application::IsRunning() const
{
	return m_isRunning;
}

void Application::Update()
{
	sf::Time elapsedTime = m_clock.restart();
	m_window.clear();
	HandleInput();

	///Other draw functions here.
	m_gui.draw();
	m_window.display();
}


void Application::HandleInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		m_gui.handleEvent(event);
		switch (event.type)
		{
			case sf::Event::Closed:
				m_window.close();
				m_isRunning = false;
				return;

			default:
				break;
		}
	}
}