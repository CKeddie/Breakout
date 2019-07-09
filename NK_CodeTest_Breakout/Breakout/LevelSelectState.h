#pragma once
#include "BaseGameState.h"
#include "UIButton.h"

class LevelBuilder;

/*
	state for allowing the user to select a level they would like to play
	and sets up a new default state with the selected level schema
*/
class LevelSelectState :
	public BaseGameState
{
public:
	LevelSelectState(Application &);

private:

	void Back();
	void LoadLevel(int);

	LevelBuilder & m_levelBuilder;
};

