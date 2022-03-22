#include "AlgoDisplayState.hpp"

void AlgoDisplayState::OnEntry(Application* app)
{
    m_randomGenerator.seed(m_randomDevice());
    generateData();
}

void AlgoDisplayState::OnExit()
{
}

void AlgoDisplayState::Draw(sf::RenderWindow & window)
{
    m_dataDisplay.draw(window, sf::RenderStates());
}

void AlgoDisplayState::Update(Application* app, sf::Time elapTime)
{
    if (m_begin)
    {
        if (!m_dataDisplay.isAnimating())
        {
            if(m_commands.empty())
            {
                m_begin = false;
                return;
            }
            Command* cmd = m_commands.front();
            cmd->execute(m_dataDisplay);
            m_commands.pop();
            m_usedCommands.push(cmd);
        }
        else
            m_dataDisplay.update(elapTime);
    }
}

void AlgoDisplayState::HandleEvent(sf::Event& event, sf::RenderWindow & window)
{
    if(!m_begin)
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                shuffleData();
                break;
            case sf::Event::MouseButtonPressed:
                m_commands = Algo::SelectionSort(m_shortData);
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

void AlgoDisplayState::shuffleData()
{
    std::shuffle(m_shortData.begin(), m_shortData.end(), m_randomGenerator);
    m_dataDisplay.setData(m_shortData);
}

void AlgoDisplayState::generateData()
{
    m_shortData.reserve(m_numDataEntries);
    m_shortData.resize(m_numDataEntries);
    for (auto i = 0; i < m_shortData.size(); i++)
        m_shortData[i] = i;
    m_dataDisplay.setData(m_shortData);
}