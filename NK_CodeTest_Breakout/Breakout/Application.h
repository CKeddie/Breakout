#pragma once

#include "SFML\Graphics.hpp"


#include "InputHandler.h"

#include "ContentManager.h"
#include "AudioManager.h"
#include "GameStateManager.h"

#include "LevelBuilder.h"

/*
	Application class used for centralising resources and management classes
	for the rest of the application
*/
class Application final
{
public:
	Application(sf::Vector2i, std::string title);
	~Application();

	void Tick(sf::Time &);
	void CleanUp();

	ContentManager & GetContent();
	GameStateManager & GetGameStateManager();
	LevelBuilder & GetLevelBuilder();
	AudioManager & GetAudioManager();

	bool IsRunning();
	void Exit();
	void SetPaused(bool state);
	bool GetPaused();

	sf::FloatRect GetFrame();

private:

	bool m_isRunning = true;
	bool m_isPaused = false;

	ContentManager m_contentManager;
	GameStateManager m_gameStateManager;
	LevelBuilder m_levelBuilder;

	sf::VideoMode m_videoMode;
	sf::RenderWindow * m_window;
	sf::Color m_backgroundColor = sf::Color(100, 149, 237); //cornflower blue
	sf::Vector2i m_screenDimensions;
};