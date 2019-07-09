#pragma once

#include "SFML\System\Vector2.hpp"
#include "Component.h"

/*
	physics component for applying a standard motion to all attached bodies
*/	
class PhysicsBody : 
	public Component
{

public:
	PhysicsBody(Entity &);

	sf::Vector2f& GetVelocity();
	void SetVelocity(sf::Vector2f velocity);
	void AddVelocity(sf::Vector2f amount);

	sf::Vector2f& GetAcceleration();
	void SetAcceleration(sf::Vector2f);
	void AddAcceleration(sf::Vector2f);

	float GetFakeInertia();
	void SetFakeInertia(float value);

	void SetMinVelocity(float mag);
	void SetMaxVelocity(float mag);

	void Update(sf::Time&)override;
	void Draw(sf::RenderWindow&)override;

protected:

	float m_minVelocity = 500.0f, m_maxVelocity = 1000.0f;
	float m_fakeInertia = 1.0f;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
};

