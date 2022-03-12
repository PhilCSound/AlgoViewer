#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "SFML/Graphics.hpp"

class DataDeck : public sf::Drawable
{
public:
    DataDeck();
    std::vector<short> getCopyOfData();
    void generateData();
    void shuffleData();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    const unsigned int MAX_NUM_DATA = 100;
    const float PIX_SIZE = 8.0f;
    sf::VertexArray m_vertexArray;
    std::vector<short> m_shortData;
    std::mt19937 m_randomGenerator;
    std::random_device m_randomDevice;

    void CreateVertexArray();
};