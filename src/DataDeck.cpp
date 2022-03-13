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

void DataDeck::lookAtIndex(int index, bool indexI)
{
    m_animState = EnumAnimationState::LOOKING;
    m_elapsedTime = sf::Time::Zero;
    if (indexI)
    {
        ChangeQuadColor(m_indexI, DEF_COLOR_1, DEF_COLOR_2);
        m_indexI = index;
        ChangeQuadColor(m_indexI, INDEX_I_COLOR_1, INDEX_I_COLOR_2);
    }
    else
    {
        ChangeQuadColor(m_indexJ, DEF_COLOR_1, DEF_COLOR_2);
        m_indexJ = index;
        ChangeQuadColor(m_indexJ, INDEX_J_COLOR_1, INDEX_J_COLOR_2);
    }
}

const bool DataDeck::isAnimating() const
{
    return (m_animState != EnumAnimationState::NOT_ANIM);
}

void DataDeck::update(sf::Time dt)
{
    m_elapsedTime += dt;
    switch(m_animState)
    {
        case EnumAnimationState::LOOKING:
            if (m_elapsedTime.asMilliseconds() > LOOK_ANIM_IN_MS)
            {
                StopAnim();
                break;
            }
        default:
            break;
    }
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
        quad[0].color = DEF_COLOR_1;
        quad[1].color = DEF_COLOR_2;
        quad[2].color = DEF_COLOR_2;
        quad[3].color = DEF_COLOR_1;
        i++;
    }
}

void DataDeck::ChangeQuadColor(int index, sf::Color color1, sf::Color color2)
{
    sf::Vertex* quad = &m_vertexArray[index * 4];
    quad[0].color = color1;
    quad[1].color = color2;
    quad[2].color = color2;
    quad[3].color = color1;
}

void DataDeck::StopAnim()
{
    m_animState = EnumAnimationState::NOT_ANIM;
    m_elapsedTime = sf::Time::Zero;
}