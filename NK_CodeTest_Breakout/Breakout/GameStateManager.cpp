#include <SFML\Graphics.hpp>
#include "GameStateManager.h"

GameStateManager::GameStateManager()
{
}


GameStateManager::~GameStateManager()
{
}

void GameStateManager::Update(sf::Time & time)
{
	if (m_states.size() > 0)
		m_states.top()->Update(time);
}

void GameStateManager::Draw(sf::RenderWindow & renderer)
{
	if (m_states.size() > 0)
		m_states.top()->Draw(renderer);
}

void GameStateManager::PushState(BaseGameState * gameState)
{
	m_states.push(gameState);
}

void GameStateManager::ReplaceState(BaseGameState * gameState)
{
	m_states.pop();
	m_states.push(gameState);
}

void GameStateManager::PopState()
{
	if (m_states.size() > 0)
	{
		BaseGameState * state = m_states.top();
		m_states.pop();

		state->CleanUp();

		delete state;
		state = nullptr;
	}
}

void GameStateManager::ChangeState(BaseGameState * gameState)
{
	Flush();
	PushState(gameState);
}

void GameStateManager::Flush()
{
	while (m_states.size() > 0)
	{
		BaseGameState * state = m_states.top();
		m_states.pop();

		state->CleanUp();

		delete state;
		state = nullptr;
	}
}

bool GameStateManager::IsEmpty()
{
	return m_states.size() == 0;
}
