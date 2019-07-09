#include "MenuState.h"
#include "Application.h"
#include "GameStates.hpp"
#include "UIButton.h"
MenuState::MenuState(Application& app)
	: BaseGameState::BaseGameState(app)
{
	ContentManager & content = app.GetContent();
	sf::FloatRect frame = app.GetFrame();

	sf::Texture & buttonUp = content.GetTexture("blue_button_up");
	sf::Texture & buttonDown = content.GetTexture("blue_button_hover");
	sf::Texture & buttonHover = content.GetTexture("blue_button_down");

	UIButton * btnNewGame = new UIButton();
	btnNewGame->SetText("New Game");
	btnNewGame->LoadFunction(std::bind(&MenuState::PushNewGame, this));
	btnNewGame->LoadTexture(buttonUp, UIButtonState::Released);
	btnNewGame->LoadTexture(buttonHover, UIButtonState::Hover);
	btnNewGame->LoadTexture(buttonDown, UIButtonState::Pressed);
	btnNewGame->SetPosition(sf::Vector2f(frame.width/2, ((frame.height / 4) * 3)) );
	m_UIHandler.AddUIElement(btnNewGame);

	UIButton * btnInstructions = new UIButton();
	btnInstructions->SetText("Help");
	btnInstructions->LoadTexture(buttonUp, UIButtonState::Released);
	btnInstructions->LoadTexture(buttonHover, UIButtonState::Hover);
	btnInstructions->LoadTexture(buttonDown, UIButtonState::Pressed);
	btnInstructions->SetPosition(sf::Vector2f(frame.width / 2, ((frame.height / 4) * 3) + 50));
	btnInstructions->LoadFunction(std::bind(&MenuState::PushInstructions, this));
	m_UIHandler.AddUIElement(btnInstructions);

	UIButton * btnQuit = new UIButton();
	btnQuit->SetText("Quit");
	btnQuit->LoadTexture(buttonUp, UIButtonState::Released);
	btnQuit->LoadTexture(buttonHover, UIButtonState::Hover);
	btnQuit->LoadTexture(buttonDown, UIButtonState::Pressed);
	btnQuit->SetPosition(sf::Vector2f(frame.width/2, ((frame.height / 4) * 3) + 100));
	btnQuit->LoadFunction(std::bind(&MenuState::Quit, this));
	m_UIHandler.AddUIElement(btnQuit);

	UILable * title = new UILable();
	title->SetPosition(sf::Vector2f(frame.width / 2, frame.height / 2));
	title->SetText("BREAKOUT");
	title->SetSize(sf::Vector2f(2, 2));
	m_UIHandler.AddUIElement(title);
}


void MenuState::PushInstructions()
{

	m_gameStateManager.PushState(new InstructionState(m_application));
}

void MenuState::PushNewGame()
{
	m_gameStateManager.PushState(new LevelSelectState(m_application));
}

void MenuState::Quit()
{
	m_gameStateManager.PopState();
}