#pragma once

#include "SFML\Graphics.hpp"
#include <iostream>
#include "UIElement.h"

/*
	UI handler, for implicit management and deallocation of GUI elements in each game state.
*/
class UIHandler final
{
public:
	UIHandler();
	~UIHandler();

	void Update(sf::Time&);
	void Draw(sf::RenderWindow&);
	void CleanUp();

	void SetFont(sf::Font&);
	sf::Font& GetFont();
	void AddUIElement(UIElement * element);

private:

	sf::Font * m_font;
	std::vector<UIElement*> m_uiElements;

};

