#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include <unordered_map>

/*
	static input wrapper/handler to allow input code throughout the codebase without need for a reference.
*/
class InputHandler
{
public:
	static InputHandler * Instance()
	{
		if (s_instance == nullptr)
			s_instance = new InputHandler();

		return s_instance;
	}


	static void Poll(sf::RenderWindow&, sf::Event&);
	
	static bool IsMouseButtonPressed(sf::Mouse::Button);
	static bool IsMouseButtonReleased(sf::Mouse::Button);
	static bool IsMouseButtonDown(sf::Mouse::Button);

	static sf::Vector2f MousePosition();

	static bool IsKeyPressed(sf::Keyboard::Key);
	static bool IsKeyReleased(sf::Keyboard::Key);
	static bool IsKeyDown(sf::Keyboard::Key);



private:
	
	static InputHandler * s_instance;

	// Keyboard Keys
	int m_keyStateCurrent[256];
	int m_keyStatePrevious[256];
	
	// Mouse Buttons
	int m_mouseButtonsCurrent[5];
	int m_mouseButtonsPrevious[5];

	sf::Vector2i m_mousePosition;
};

