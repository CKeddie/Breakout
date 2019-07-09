#include "InputHandler.h"
#include <iostream>

InputHandler * InputHandler::s_instance = nullptr;

// checks for input events and interprets them

void InputHandler::Poll(sf::RenderWindow & window, sf::Event & e)
{
	// get mouse position relative to window
	Instance()->m_mousePosition = sf::Mouse::getPosition(window);
   
	// update/flip key and button buffers
	memcpy(Instance()->m_keyStatePrevious, Instance()->m_keyStateCurrent, 256);
	memcpy(Instance()->m_mouseButtonsPrevious, Instance()->m_mouseButtonsCurrent, 5);

	// check for input and update buffers accordingly
	switch (e.type)
	{
	case sf::Event::MouseButtonPressed:
		Instance()->m_mouseButtonsCurrent[e.key.code] = true;
		break;

	case sf::Event::MouseButtonReleased:
		Instance()->m_mouseButtonsCurrent[e.key.code] = false;
		break;

	case sf::Event::KeyPressed:
		Instance()->m_keyStateCurrent[e.key.code] = true;
		break;

	case sf::Event::KeyReleased:
		Instance()->m_keyStateCurrent[e.key.code] = false;
		break;

	}
}

// returns true if the button has been pressed
bool InputHandler::IsMouseButtonPressed(sf::Mouse::Button key)
{
	return Instance()->m_mouseButtonsCurrent[key] && !Instance()->m_mouseButtonsPrevious[key];
}

// returns true if the button has been released
bool InputHandler::IsMouseButtonReleased(sf::Mouse::Button key)
{
	return !Instance()->m_mouseButtonsCurrent[key] && Instance()->m_mouseButtonsPrevious[key];
}

// returns true if the button is held down
bool InputHandler::IsMouseButtonDown(sf::Mouse::Button key)
{
	return Instance()->m_mouseButtonsCurrent[key] && Instance()->m_mouseButtonsPrevious[key];
}

// returns the mouse position relative to the application window
sf::Vector2f InputHandler::MousePosition()
{
	return (sf::Vector2f)Instance()->m_mousePosition;
}

// returns true if the key has been pressed
bool InputHandler::IsKeyPressed(sf::Keyboard::Key key)
{
	return Instance()->m_keyStateCurrent[key] && !Instance()->m_keyStatePrevious[key];
}

// returns true if the key has been released
bool InputHandler::IsKeyReleased(sf::Keyboard::Key key)
{
	return !Instance()->m_keyStateCurrent[key] && Instance()->m_keyStatePrevious[key];
}

// returns true if the key is held down
bool InputHandler::IsKeyDown(sf::Keyboard::Key key)
{
	return Instance()->m_keyStateCurrent[key] && Instance()->m_keyStatePrevious[key];
}


