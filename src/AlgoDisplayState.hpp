#pragma once
#include "State.hpp"
#include "SFML/Graphics.hpp"
#include "DataDeck.hpp"

class AlgoDisplayState : public State
{
public:
	void OnEntry(Application * app) override;
	void OnExit() override;

	void Draw(sf::RenderWindow & window) override;
	void Update(Application * app, sf::Time elapTime) override;
	void HandleEvent(sf::Event& event, sf::RenderWindow & window) override;

	void Pause() override;
	void Unpause() override;

private:
	DataDeck m_data;
};