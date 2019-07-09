#pragma once


#include <SFML\Graphics.hpp>
#include "UIHandler.h"
#include "UIButton.h"

class AudioManager;
class Application;
class GameStateManager;
class ContentManager;

/*
	Base state of any concrete implementation of a state within the application
*/
class BaseGameState
{

public:
	BaseGameState(Application &);
	virtual ~BaseGameState() = default;

	virtual void Update(sf::Time & deltaTime);
	virtual	void Draw(sf::RenderWindow & renderer);
	virtual void CleanUp();
	
protected:

	UIHandler m_UIHandler;
	Application & m_application;
	GameStateManager & m_gameStateManager;
	ContentManager & m_contentManager;
};

