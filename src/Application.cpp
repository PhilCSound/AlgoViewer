#include "Application.hpp"

Application::Application()
{
	m_window.create(sf::VideoMode(800, 800, 32), "Algo Viewer");
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

	if (m_stackOfStates.size())
    {
		m_stackOfStates.back()->Update(this, elapsedTime);
	    m_stackOfStates.back()->Draw(m_window);
	}
	///Other draw functions here.
	m_gui.draw();
	m_window.display();
}

void Application::ChangeState(State * _state)
{
	if (!m_stackOfStates.empty()) {
		m_stackOfStates.back()->OnExit();
		m_stackOfStates.pop_back();
	}
	_state->OnEntry(this);
	m_stackOfStates.push_back(_state);

}

void Application::PushState(State * _state)
{
	if (!m_stackOfStates.empty())
		m_stackOfStates.back()->Pause();

	_state->OnEntry(this);
	m_stackOfStates.push_back(_state);
}

void Application::PopState()
{
	if (m_stackOfStates.empty()) {
		m_window.close();
	}
    delete m_stackOfStates.back();
	m_stackOfStates.pop_back();
	m_stackOfStates.back()->Unpause();
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

			case sf::Event::LostFocus:
                if (m_stackOfStates.size())
				    m_stackOfStates.back()->Pause();
				break;

			case sf::Event::GainedFocus:
                if (m_stackOfStates.size())
				    m_stackOfStates.back()->Unpause();
				break;

			case sf::Event::Resized:
                if (m_stackOfStates.size())
				    m_stackOfStates.back()->HandleEvent(event, m_window);
				break;

			default:
                if (m_stackOfStates.size())
				    m_stackOfStates.back()->HandleEvent(event, m_window);
				break;
		}
	}
}