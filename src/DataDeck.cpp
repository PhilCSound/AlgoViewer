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

void DataDeck::swap(int indexL, int indexR)
{
    m_animState = EnumAnimationState::SWAPPING;
    m_elapsedTime = sf::Time::Zero;
    m_indexToSwapL = indexL;
    m_indexToSwapR = indexR;
}


const bool DataDeck::isAnimating() const
{
    return (m_animState != EnumAnimationState::NOT_ANIM);
}

void DataDeck::update(sf::Time dt)
{
    m_elapsedTime += dt;
    float theta = m_elapsedTime.asMilliseconds() / SWAP_ANIM_IN_MS;
    theta = theta;
    switch(m_animState)
    {
        case EnumAnimationState::LOOKING:
            if (m_elapsedTime.asMilliseconds() > LOOK_ANIM_IN_MS)
            {
                StopAnim();
                break;
            }
            break;
        case EnumAnimationState::SWAPPING:

            if (theta >= 1.0f)
            {
                theta = 1.0f;
                AnimQuadSwap(m_indexToSwapL, m_indexToSwapR, theta);
                SwapIndexes(m_indexToSwapL, m_indexToSwapR);
                StopAnim();
                return;
            }
            else
                AnimQuadSwap(m_indexToSwapL, m_indexToSwapR, theta);
            return;
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
        sf::Vector2f botLeftPos = sf::Vector2f(i * PIX_SIZE, pixMax);
        ChangeQuadPos(i, botLeftPos, data);
        ChangeQuadColor(i, DEF_COLOR_1, DEF_COLOR_2);
        i++;
    }
}

void DataDeck::ChangeQuadPos(int index, sf::Vector2f botLeftPos, short data)
{
    sf::Vertex* quad = &m_vertexArray[index * 4];
    float dataHeight = PIX_SIZE * data;
    quad[0].position = botLeftPos;
    quad[1].position = sf::Vector2f(botLeftPos.x, botLeftPos.y - dataHeight);
    quad[2].position = sf::Vector2f(botLeftPos.x + PIX_SIZE, botLeftPos.y - dataHeight);
    quad[3].position = sf::Vector2f(botLeftPos.x + PIX_SIZE, botLeftPos.y);
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

//Theta is a value between 0.0f and 1.0f that indicates when fully swapped
void DataDeck::AnimQuadSwap(int index1, int index2, float theta)
{
    int pixMax = MAX_NUM_DATA * PIX_SIZE;
    //Quad1's default botLeft position (at theta = 0.0f) followed by Quad 2
    sf::Vector2f quad1InitPos = sf::Vector2f(index1 * PIX_SIZE, pixMax);
    sf::Vector2f quad2InitPos = sf::Vector2f(index2 * PIX_SIZE, pixMax);

    sf::Vector2f quadOffset = (quad2InitPos - quad2InitPos) * theta;
    ChangeQuadPos(index1, quad1InitPos + quadOffset, m_shortData[index1]);
    ChangeQuadPos(index2, quad2InitPos - quadOffset, m_shortData[index2]);
}

void DataDeck::SwapIndexes(int index1, int index2)
{
    int pixMax = MAX_NUM_DATA * PIX_SIZE;
    std::swap(m_shortData.at(index1), m_shortData.at(index2));
    sf::Vector2f quad1InitPos = sf::Vector2f(index1 * PIX_SIZE, pixMax);
    sf::Vector2f quad2InitPos = sf::Vector2f(index2 * PIX_SIZE, pixMax);
    ChangeQuadPos(index1, quad1InitPos, m_shortData.at(index1));
    ChangeQuadPos(index2, quad2InitPos, m_shortData.at(index2));
}
