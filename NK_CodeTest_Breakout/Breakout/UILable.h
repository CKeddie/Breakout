#pragma once
#include "UIElement.h"
class UILable :
	public UIElement
{
public:

	UILable();

	void Update(sf::Time&) override;
	
	void Draw(sf::RenderWindow&) override;

	void SetText(std::string);
	
	void SetFont(sf::Font&);

	void SetPosition(sf::Vector2f) override;

	void SetSize(const sf::Vector2f &);
	
protected:
	
	sf::Text m_text;

};

