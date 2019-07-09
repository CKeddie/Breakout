#pragma once
#include "BaseGameState.h"

/*
	basic initial menu state that displays the game title and provides 
	gui/functionality for navigating the application.
*/
class MenuState final :
	public BaseGameState
{
public:

	MenuState(Application & app);

private:

	void PushInstructions();
	void PushNewGame();
	void Quit();
};

