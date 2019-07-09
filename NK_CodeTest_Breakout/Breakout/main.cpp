#include "Application.h"

sf::Vector2i screenRes(1024,768);
Application m_application(screenRes, "Breakout");

int main()
{	
	// initialise clock for delta time
	sf::Clock deltaClock;

	// application loop	
	while (m_application.IsRunning())
	{	
		// reset clock for deltatime
		sf::Time deltaTime = deltaClock.restart();
	
		// update application
		m_application.Tick(deltaTime);
		
	}

	// deallocate throughout the application
	m_application.CleanUp();

	return 0;
}