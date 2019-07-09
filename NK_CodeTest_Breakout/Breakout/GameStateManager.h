#pragma once

#include <stack>
#include "BaseGameState.h"

namespace sf
{
	class Time;
	class RenderWindow;
}

/*
	stack-based game state manager for loading/unloading game states to the application
*/
class GameStateManager final
{
public:
	
	GameStateManager();
	~GameStateManager();

	void Update(sf::Time&);
	void Draw(sf::RenderWindow&);

	void ReplaceState(BaseGameState*);
	void PushState(BaseGameState*);
	void PopState();
	void ChangeState(BaseGameState*);
	void Flush();

	bool IsEmpty();
private:

	std::stack<BaseGameState*> m_states;
	
};

