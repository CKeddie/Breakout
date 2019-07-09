#pragma once
#include "Entity.h"
#include "SFML\Graphics.hpp"

class Paddle 
	: public Entity
{
public:
	Paddle(sf::Vector2f, sf::Vector2f);
	
	void Move(float x);

	void Update(sf::Time &) override;
	void Draw(sf::RenderWindow&) override;
	
	void OnCollisionEnter(Manifold) override;
	void OnCollisionStay(Manifold) override;
	void OnCollisionExit(Manifold) override;

private: 

	Collider * m_collider;
	PhysicsBody * m_physicsBody;
	SpriteRenderer * m_spriteRenderer;

};

