#pragma once

#include <functional>
#include <iostream>

#include "UIElement.h"
#include "UILable.h"

class BaseGameState;

enum UIButtonState
{
	Released = 0,
	Hover,
	Pressed
};

class UIButton 
	: public UIElement
{
public:
	UIButton();

	void Update(sf::Time&) override;
	void Draw(sf::RenderWindow&) override;
	void SetPosition(sf::Vector2f)override;

	void SetText(std::string);
	void LoadTexture(sf::Texture&, UIButtonState);
	void LoadFunction(std::function<void(void)>);
	void SetFont(sf::Font&)override;
	sf::Vector2f GetSize();

	void CleanUp() override;

protected:
	
	UILable m_lable;
	
	std::function<void(void)>	m_function;

	sf::Texture m_onButtonState[3];
	sf::Sprite m_displaySprite;
};

