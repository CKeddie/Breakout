#pragma once

#include "SFML\Graphics.hpp"
/*
	base object for any user interface element to be displayed
*/
class UIElement
{
public:
	UIElement();
	virtual ~UIElement() = default;

	virtual void Update(sf::Time&) = 0;
	virtual void Draw(sf::RenderWindow&) = 0;

	sf::Vector2f GetPosition();	
	virtual void SetPosition(sf::Vector2f v = sf::Vector2f());

	void SetActive(bool state);
	bool GetActive();

	void SetVisibility(bool state);
	bool GetVisibility();

	virtual void SetFont(sf::Font&);

	virtual void CleanUp();

protected:
	
	bool m_active = true;
	bool m_visibility = true;

	sf::Font*m_font;

	sf::Vector2f m_position;	
};

