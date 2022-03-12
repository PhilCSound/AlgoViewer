#include "DataDeck.hpp"

DataDeck::DataDeck()
{
    m_randomGenerator.seed(m_randomDevice());
    m_vertexArray.setPrimitiveType(sf::Quads);
    m_vertexArray.resize(MAX_NUM_DATA * 4);
    generateData();
}

std::vector<short> DataDeck::getCopyOfData()
{
    return m_shortData;
}

void DataDeck::generateData()
{
    m_shortData.reserve(MAX_NUM_DATA);
    m_shortData.resize(MAX_NUM_DATA);
    for (auto i = 0; i < m_shortData.size(); i++)
        m_shortData[i] = i;
    CreateVertexArray();
}

void DataDeck::shuffleData()
{
    std::shuffle(m_shortData.begin(), m_shortData.end(), m_randomGenerator);
    CreateVertexArray();
}

void DataDeck::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_vertexArray, states);
}

void DataDeck::CreateVertexArray()
{
    int i = 0;
    int pixMax = MAX_NUM_DATA * PIX_SIZE;
    for (short& data : m_shortData)
    {
        sf::Vertex* quad = &m_vertexArray[i * 4];
        quad[0].position = sf::Vector2f(i * PIX_SIZE, pixMax);
        quad[1].position = sf::Vector2f(i * PIX_SIZE, pixMax - PIX_SIZE * data);
        quad[2].position = sf::Vector2f((i + 1) * PIX_SIZE, pixMax - PIX_SIZE * data);
        quad[3].position = sf::Vector2f((i + 1)* PIX_SIZE, pixMax);
        //Color
        quad[0].color = sf::Color(102, 126, 234);
        quad[1].color = sf::Color(118, 75, 162);
        quad[2].color = sf::Color(118, 75, 162);
        quad[3].color = sf::Color(102, 126, 234);
        i++;
    }
}