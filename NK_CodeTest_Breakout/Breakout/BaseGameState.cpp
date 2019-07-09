#include "BaseGameState.h"
#include "Application.h"
#include "GameStates.hpp"
#include "ContentManager.h"
#include "GameStateManager.h"
#include "AudioManager.h"

BaseGameState::BaseGameState(Application & app)
	: m_application(app)
	, m_gameStateManager(app.GetGameStateManager())
	, m_contentManager(app.GetContent())
{

	m_UIHandler.SetFont(m_contentManager.GetFont("KenneyBlocks"));
}

void BaseGameState::Update(sf::Time & deltaTime)
{
	m_UIHandler.Update(deltaTime);
}

void BaseGameState::Draw(sf::RenderWindow & renderer)
{
	m_UIHandler.Draw(renderer);

}

void BaseGameState::CleanUp()
{
	m_UIHandler.CleanUp();
}
