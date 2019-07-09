#include "InstructionState.h"
#include "ContentManager.h"
#include "GameStateManager.h"
#include "Application.h"


InstructionState::InstructionState(Application & app)
	: BaseGameState::BaseGameState(app)
{	
	sf::FloatRect frame = app.GetFrame();

	// get assets for buttins
	sf::Texture & buttonUp = m_contentManager.GetTexture("blue_button_up");
	sf::Texture & buttonDown = m_contentManager.GetTexture("blue_button_hover");
	sf::Texture & buttonHover = m_contentManager.GetTexture("blue_button_down");

	UIButton * back = new UIButton();
	back->SetText("Menu");
	back->SetPosition(sf::Vector2f(frame.left + 105, frame.height - 35));
	back->LoadTexture(buttonDown, Pressed);
	back->LoadTexture(buttonHover, Hover);
	back->LoadTexture(buttonUp, Released);
	back->LoadFunction(std::bind(&InstructionState::Back, this));
	m_UIHandler.AddUIElement(back);

	UILable * instruction1 = new UILable();
	instruction1->SetText("Use 'A' and 'D' to move the paddle Left and Right.");
	instruction1->SetPosition(sf::Vector2f(frame.width / 2, frame.top + 100));	
	m_UIHandler.AddUIElement(instruction1);

	UILable * instruction2 = new UILable();
	instruction2->SetText("Destroy all the bricks in the level to win.");
	instruction2->SetPosition(sf::Vector2f(frame.width / 2, frame.top + 150));	
	m_UIHandler.AddUIElement(instruction2);
	
	UILable * instruction3 = new UILable();
	instruction3->SetText("Don't run out of lives.");
	instruction3->SetPosition(sf::Vector2f(frame.width / 2, frame.top + 200));
	m_UIHandler.AddUIElement(instruction3);
}


InstructionState::~InstructionState()
{
}

void InstructionState::Back()
{
	m_gameStateManager.PopState();
}
