#include "DataDeck.hpp"

DataDeck::DataDeck()
{
    m_vertexArray.setPrimitiveType(sf::Quads);
}

void DataDeck::setData(std::vector<short> data)
{
    m_shortData = data;
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
    m_vertexArray.resize(m_shortData.size() * 4);
    //Max element returns an iterator, so we dereference it.
    int maxVal = *std::max_element(m_shortData.begin(), m_shortData.end());
    m_pixMax = m_shortData.size() * PIX_SIZE;

    //TODO: This is 2N~ can speed up though by implenting maxval in the loop
    for (short& data : m_shortData)
    {
        sf::Vector2f botLeftPos = sf::Vector2f(i * PIX_SIZE, m_pixMax);
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
    //Quad1's default botLeft position (at theta = 0.0f) followed by Quad 2
    sf::Vector2f quad1InitPos = sf::Vector2f(index1 * PIX_SIZE, m_pixMax);
    sf::Vector2f quad2InitPos = sf::Vector2f(index2 * PIX_SIZE, m_pixMax);

    sf::Vector2f quadOffset = (quad2InitPos - quad2InitPos) * theta;
    ChangeQuadPos(index1, quad1InitPos + quadOffset, m_shortData[index1]);
    ChangeQuadPos(index2, quad2InitPos - quadOffset, m_shortData[index2]);
}

void DataDeck::SwapIndexes(int index1, int index2)
{
    std::swap(m_shortData.at(index1), m_shortData.at(index2));
    sf::Vector2f quad1InitPos = sf::Vector2f(index1 * PIX_SIZE, m_pixMax);
    sf::Vector2f quad2InitPos = sf::Vector2f(index2 * PIX_SIZE, m_pixMax);
    ChangeQuadPos(index1, quad1InitPos, m_shortData.at(index1));
    ChangeQuadPos(index2, quad2InitPos, m_shortData.at(index2));
}
