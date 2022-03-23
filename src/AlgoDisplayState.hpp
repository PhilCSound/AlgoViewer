#pragma once
#include "State.hpp"
#include "SFML/Graphics.hpp"
#include "AlgoVisualizer.hpp"
#include "Algorithms.hpp"
#include <random>
#include <chrono>

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
	int m_numDataEntries = 50;
    std::vector<short> m_shortData;
	AlgoVisualizer m_dataDisplay;
	bool m_begin = false;
	//Command queues
	std::queue<Command*> m_commands;
	std::queue<Command*> m_usedCommands;
	//For Randomizing data.
	std::mt19937 m_randomGenerator;
    std::random_device m_randomDevice;

	/*
	|	Private Functions
	*/
	void shuffleData();
	void generateData();

};