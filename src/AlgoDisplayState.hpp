#pragma once
#include "State.hpp"
#include "SFML/Graphics.hpp"
#include "DataDeck.hpp"
#include "Algorithms.hpp"

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
	bool m_begin = false;
	std::queue<Command*> m_commands;
	std::queue<Command*> m_usedCommands;

};