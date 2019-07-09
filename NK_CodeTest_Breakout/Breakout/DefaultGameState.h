#pragma once
#include "BaseGameState.h"

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "CollisionHandler.h"


#include "SFML\Graphics.hpp"
#include "SFMLMath.hpp"
#include "LevelBuilder.h"

/*
	concrete implementation of the default state of each breakout game
	contains a bat and ball, and construction for level schemas
	handles collision detection
*/
class DefaultGameState :
	public BaseGameState
{
public:

	DefaultGameState(Application &, LevelSchema blueprint);
	void Construct(LevelSchema blueprint);

	void Update(sf::Time & deltaTime) override;

	void Draw(sf::RenderWindow & renderWindow) override;

	void CleanUp() override;

private:

	void DetectCollisions(sf::Time & deltaTime);

	CollisionHandler * m_collisionHandler;
	std::vector<Brick*> bricks;
	Ball * m_ball;
	Paddle * m_paddle;

	UILable * lives;

	int m_lives = 3;
	bool m_initial = true;
	bool m_run = false;

	sf::FloatRect m_border;
};

