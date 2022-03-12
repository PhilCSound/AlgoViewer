#pragma once
#include "Application.hpp"

class Application;

class State {

public:
	virtual void OnEntry(Application* app) = 0;
	virtual void OnExit() = 0;

	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Update(Application* app, sf::Time elapTime) = 0;
	virtual void HandleEvent(sf::Event& event, sf::RenderWindow& window) = 0;
	
	virtual void Pause() = 0;
	virtual void Unpause() = 0;
};