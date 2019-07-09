#pragma once
#include "BaseGameState.h"
#include "UIButton.h"
#include "UILable.h"

/*
	state that displays a win/loss message after each game
	and provides access back to the main menu.
*/
class FinishState :
	public BaseGameState
{
public:
	FinishState(Application &, bool);
	
	void Update(sf::Time&) override;
	void Draw(sf::RenderWindow&) override;

private:

	void Back();
};

