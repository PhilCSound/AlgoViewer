#pragma once
#include "State.hpp"
#include "SFML/Graphics.hpp"
#include "TGUI/TGUI.hpp"
#include "AlgoVisualizer.hpp"
#include "Algorithms.hpp"
#include <random>
#include <algorithm>

class AlgoDisplayState : public State
{
public:
	void OnEntry(Application * app) override;
	void OnExit(Application* app) override;

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
	sf::View m_displayView;
	//TGUI
	tgui::GuiSFML m_tgui;
	//Command queues
	std::deque<Command*> m_commands;
	std::deque<Command*> m_usedCommands;
	//For Randomizing data.
	std::mt19937 m_randomGenerator;
	tgui::String m_selectedAlgo = "";
	/*
	|	Private Functions
	*/
	void shuffleData();
	void generateLinearData();
	void generateRandomData();
	void resizeData();
	void createUI();
	void updateDisplayView();
	void beginAlgorithm(bool replay = false);
	void doneWithAlgorithm();
	void getAlgorithm();
	void log(const std::string string);
};