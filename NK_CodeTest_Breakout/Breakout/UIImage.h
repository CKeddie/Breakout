#pragma once
#include "UIElement.h"
class UIImage :
	public UIElement
{
public:
	UIImage();
	~UIImage();

	void Update(sf::Time&)override;
	void Draw(sf::RenderWindow&)override;
	void SetPosition(sf::Vector2f)override;

protected:

	sf::Sprite m_displaySprite;

};

