#pragma once
#include <vector>
#include <algorithm>
#include "SFML/Graphics.hpp"
#include "EnumAnimationState.hpp"

class DataDeck : public sf::Drawable
{
public:
    DataDeck();
    void setData(std::vector<short> data);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void lookAtIndex(int index, bool indexI = true);
    void swap(int indexL, int indexR);
    const bool isAnimating() const;
    void update(sf::Time dt);

private:
    const float PIX_SIZE = 8.0f;
    const float LOOK_ANIM_IN_MS = 3.0f;
    const float SWAP_ANIM_IN_MS = 6.0f;
    const sf::Color DEF_COLOR_1 = sf::Color(102, 126, 234);
    const sf::Color DEF_COLOR_2 = sf::Color(118, 75, 162);
    const sf::Color INDEX_I_COLOR_1 = sf::Color(19, 84, 122);
    const sf::Color INDEX_I_COLOR_2 = sf::Color(128, 208, 199);
    const sf::Color INDEX_J_COLOR_1 = sf::Color(250, 208, 196);
    const sf::Color INDEX_J_COLOR_2 = sf::Color(255, 154, 158);
    sf::VertexArray m_vertexArray;
    std::vector<short> m_shortData;
    int m_indexI = 0;
    int m_indexJ = 0;
    int m_indexToSwapL = 0;
    int m_indexToSwapR = 0;
    int m_pixMax = 0;
    sf::Time m_elapsedTime;
    EnumAnimationState m_animState = EnumAnimationState::NOT_ANIM;

    void CreateVertexArray();
    void ChangeQuadPos(int index, sf::Vector2f botLeftPos, short data);
    void ChangeQuadColor(int index, sf::Color color1, sf::Color color2);
    void AnimQuadSwap(int index1, int index2, float theta);
    void StopAnim();
    void SwapIndexes(int index1, int index2);
};