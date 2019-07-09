#include "Application.h"

#include "GameStateManager.h"
#include "GameStates.hpp"
#include <sstream>

Application::Application(sf::Vector2i screenDim, std::string title)
{
	// setup screen
	m_screenDimensions = screenDim;
	m_window = new sf::RenderWindow(sf::VideoMode(screenDim.x, screenDim.y), title);
	sf::View m_view;
	
	// stream audio source
	AudioManager::PlayMusic("music_8bit_jammer.wav");
	
	// load fonts
	m_contentManager.LoadFont("Kenney Blocks.ttf", "KenneyBlocks");
	
	// load textures
	// UI
	m_contentManager.LoadTexture("UI/blue_button00.png", "blue_button_up");
	m_contentManager.LoadTexture("UI/blue_button02.png", "blue_button_hover");
	m_contentManager.LoadTexture("UI/blue_button01.png", "blue_button_down");
	
	// Game Assets
	m_contentManager.LoadTexture("Game/ballGrey.png", "ball_grey");
	m_contentManager.LoadTexture("Game/element_grey_diamond_glossy.png", "diamond_glossy");
	m_contentManager.LoadTexture("Game/element_grey_rectangle_glossy.png", "brick_glossy");
	m_contentManager.LoadTexture("Game/paddleBlu.png", "paddle");
	
	// load sounds
	AudioManager::LoadBuffer("retro_jump_bounce_12.wav","bounce");
	AudioManager::LoadBuffer("retro_misc_bass_sound_07.wav","death");
	AudioManager::LoadBuffer("retro_shield_on_deflect_06.wav","deflect");
	AudioManager::LoadBuffer("retro_spawn_appear_04.wav","spawn");
	AudioManager::LoadBuffer("bubble_effect_04.wav","bubble");

	// load levels
	int numLevels = 5;

	for (int i = 0; i < numLevels; i++)
	{
		std::stringstream ss;
		ss << "Level_" << i << ".txt";
		m_levelBuilder.LoadLevel(ss.str());
	}
	
	// enter game
	m_gameStateManager.PushState(new MenuState(*this));
}

Application::~Application()
{
}

void Application::Tick(sf::Time & deltaTime)
{
	// poll sfml events
	sf::Event e;
	while (m_window->isOpen() && m_window->pollEvent(e))
	{
		// the windows [X] button has been pressed
		if (e.type == sf::Event::Closed)
		{
			// close the window
			m_window->close();
			
			// quit the app
			m_isRunning = false;
		}

		// window is not in focus
		if (e.type == sf::Event::LostFocus)
		{
			// pause the app
			m_isPaused = true;
		}
		else if (e.type == sf::Event::GainedFocus)
		{
			// resume the app
			m_isPaused = false;
		}

		// poll input handler events
		InputHandler::Poll(*m_window, e);
	}

	// if application is paused do not draw or update
	if (GetPaused()) return;

	// update game state
	m_gameStateManager.Update(deltaTime);

	// refresh window
	m_window->clear(m_backgroundColor);

	// draw gamestate
	m_gameStateManager.Draw(*m_window);

	// show on screen
	m_window->display();
}

void Application::CleanUp()
{
	// flush all states (if any)
	m_gameStateManager.Flush();

	m_contentManager.CleanUp();

	//m_levelBuilder.CleanUp();
	
	// close window
	m_window->close();

	// delete window
	delete m_window;
	m_window = nullptr;
}

ContentManager & Application::GetContent()
{
	return m_contentManager;
}

GameStateManager & Application::GetGameStateManager()
{
	return m_gameStateManager;
}

LevelBuilder & Application::GetLevelBuilder()
{
	return m_levelBuilder;
}

bool Application::IsRunning()
{
	return !m_gameStateManager.IsEmpty() && m_isRunning;
}

void Application::Exit()
{
	m_isRunning = false;
}

void Application::SetPaused(bool state)
{
	m_isPaused = state;
}

bool Application::GetPaused()
{
	return m_isPaused;
}

sf::FloatRect Application::GetFrame()
{
	return sf::FloatRect(sf::Vector2f(), (sf::Vector2f)m_screenDimensions);
}
