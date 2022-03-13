#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "SFML/Graphics.hpp"
#include "EnumAnimationState.hpp"

class DataDeck : public sf::Drawable
{
public:
    DataDeck();
    std::vector<short> getCopyOfData();
    void generateData();
    void shuffleData();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void lookAtIndex(int index, bool indexI = true);
    const bool isAnimating() const;
    void update(sf::Time dt);

private:
    const unsigned int MAX_NUM_DATA = 100;
    const float PIX_SIZE = 8.0f;
    const float LOOK_ANIM_IN_MS = 3.0f;
    const sf::Color DEF_COLOR_1 = sf::Color(102, 126, 234);
    const sf::Color DEF_COLOR_2 = sf::Color(118, 75, 162);
    const sf::Color INDEX_I_COLOR_1 = sf::Color(19, 84, 122);
    const sf::Color INDEX_I_COLOR_2 = sf::Color(128, 208, 199);
    const sf::Color INDEX_J_COLOR_1 = sf::Color(250, 208, 196);
    const sf::Color INDEX_J_COLOR_2 = sf::Color(255, 154, 158);
    sf::VertexArray m_vertexArray;
    std::vector<short> m_shortData;
    std::mt19937 m_randomGenerator;
    std::random_device m_randomDevice;
    int m_indexI = 0;
    int m_indexJ = 0;
    sf::Time m_elapsedTime;
    EnumAnimationState m_animState = EnumAnimationState::NOT_ANIM;

    void CreateVertexArray();
    void ChangeQuadColor(int index, sf::Color color1, sf::Color color2);
    void StopAnim();
};