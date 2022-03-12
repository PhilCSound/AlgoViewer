#include "AlgoDisplayState.hpp"

void AlgoDisplayState::OnEntry(Application* app)
{
}

void AlgoDisplayState::OnExit()
{
}

void AlgoDisplayState::Draw(sf::RenderWindow & window)
{
    m_data.draw(window, sf::RenderStates());
}

void AlgoDisplayState::Update(Application* app, sf::Time elapTime)
{
}

void AlgoDisplayState::HandleEvent(sf::Event& event, sf::RenderWindow & window)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            m_data.shuffleData();
            break;
        default:
            break;
    }
}

void AlgoDisplayState::Pause()
{
}

void AlgoDisplayState::Unpause()
{
}