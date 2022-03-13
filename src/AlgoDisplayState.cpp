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
    if (m_begin)
    {
        if (!m_data.isAnimating())
        {
            if(m_commands.empty())
            {
                m_begin = false;
                return;
            }
            Command* cmd = m_commands.front();
            cmd->execute(m_data);
            m_commands.pop();
            m_usedCommands.push(cmd);
        }
        else
            m_data.update(elapTime);
    }
}

void AlgoDisplayState::HandleEvent(sf::Event& event, sf::RenderWindow & window)
{
    if(!m_begin)
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                m_data.shuffleData();
                break;
            case sf::Event::MouseButtonPressed:
                m_commands = Algo::SelectionSort(m_data.getCopyOfData());
                m_begin = true;
                break;
            default:
                break;
        }
    }
}

void AlgoDisplayState::Pause()
{
}

void AlgoDisplayState::Unpause()
{
}