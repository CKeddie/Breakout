#pragma once


#include <SFML\Graphics.hpp>
#include "Entity.h"

class Ball 
	: public Entity
{
public:

	Ball(sf::Vector2f, float, int);
	
	void OnCollisionEnter(Manifold) override;
	void OnCollisionStay(Manifold) override;
	void OnCollisionExit(Manifold) override;

	void SetColor(sf::Color);
private:
	AudioSource * m_audioSource;
	PhysicsBody * m_physicsBody;
	Collider * m_collider;
	SpriteRenderer * m_spriteRenderer;

	float m_radius;
	int m_resolution;
	
};