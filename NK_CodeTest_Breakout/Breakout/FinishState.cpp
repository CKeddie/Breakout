#include "FinishState.h"
#include "Application.h"

FinishState::FinishState(Application& app, bool winState)
	: BaseGameState::BaseGameState(app)
{
	sf::Texture & buttonUp = m_contentManager.GetTexture("blue_button_up");
	sf::Texture & buttonDown = m_contentManager.GetTexture("blue_button_hover");
	sf::Texture & buttonHover = m_contentManager.GetTexture("blue_button_down");

	sf::FloatRect frame = app.GetFrame();

	UILable * m_winLable = new UILable();
	m_winLable->SetText(winState ? "Winner!" : "Better Luck Next Time...");
	m_winLable->SetPosition(sf::Vector2f(app.GetFrame().width / 2, app.GetFrame().height / 2));
	m_UIHandler.AddUIElement(m_winLable);
	m_winLable->SetSize(sf::Vector2f(2,2));

	UIButton * back = new UIButton();
	back->SetText("Menu");
	back->SetPosition(sf::Vector2f(frame.left + 105, frame.height - 35));
	back->LoadTexture(buttonDown, Pressed);
	back->LoadTexture(buttonHover, Hover);
	back->LoadTexture(buttonUp, Released);
	back->LoadFunction(std::bind(&FinishState::Back, this));
	m_UIHandler.AddUIElement(back);
}

void FinishState::Update(sf::Time & deltaTime)
{
	BaseGameState::Update(deltaTime);
}

void FinishState::Draw(sf::RenderWindow & renderer)
{
	BaseGameState::Draw(renderer);
}

void FinishState::Back()
{
	m_gameStateManager.PopState();
}
