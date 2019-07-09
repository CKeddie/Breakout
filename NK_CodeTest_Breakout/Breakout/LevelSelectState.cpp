#include "LevelSelectState.h"
#include "Application.h"
#include "GameStates.hpp"
#include "LevelBuilder.h"
#include <functional>
#include <sstream>

LevelSelectState::LevelSelectState(Application& app)
	: BaseGameState::BaseGameState(app)
	, m_levelBuilder(app.GetLevelBuilder())
{
	// get assets for buttins
	sf::Texture & buttonUp = m_contentManager.GetTexture("blue_button_up");
	sf::Texture & buttonDown = m_contentManager.GetTexture("blue_button_hover");
	sf::Texture & buttonHover = m_contentManager.GetTexture("blue_button_down");


	sf::FloatRect frame = app.GetFrame();


	UILable * title = new UILable();
	title->SetText("Level Select");
	title->SetPosition(sf::Vector2f(frame.width / 2, 50));
	m_UIHandler.AddUIElement(title);

	// get the number of levels
	int levelCount = m_levelBuilder.GetLevelCount();

	// iterate through level count
	for (int i = 0; i < levelCount; i++)
	{
		// create button for each level
		UIButton * levelButton = new UIButton;
		
		// load textures for each button state
		levelButton->LoadTexture(buttonDown, Pressed);
		levelButton->LoadTexture(buttonHover, Hover);
		levelButton->LoadTexture(buttonUp, Released);
		levelButton->LoadFunction(std::bind(&LevelSelectState::LoadLevel, this, i));

		// construct button lable
		std::stringstream strs;
		strs << i + 1;
		levelButton->SetText("Level " + strs.str());
		
		// set position
		sf::Vector2f position;
		position.x = frame.left + (frame.width / 2.0f);
		position.y = 100 + (levelButton->GetSize().y * i);
		levelButton->SetPosition(position);

		// add button to the handler
		m_UIHandler.AddUIElement(levelButton);
	}

	// construct back button
	UIButton * back = new UIButton();
	back->SetText("Menu");
	back->SetPosition(sf::Vector2f(frame.left + 105, frame.height - 35));
	back->LoadTexture(buttonDown, Pressed);
	back->LoadTexture(buttonHover, Hover);
	back->LoadTexture(buttonUp, Released);
	back->LoadFunction(std::bind(&LevelSelectState::Back, this));
	m_UIHandler.AddUIElement(back);
}

void LevelSelectState::Back()
{
	m_gameStateManager.PopState();
}

void LevelSelectState::LoadLevel(int index)
{
	// get level schema
	LevelSchema schema;
	m_levelBuilder.GetLevel(index, schema);
	
	// construct a new default game state using the schema
	m_gameStateManager.PushState(new DefaultGameState(m_application, schema));
}
