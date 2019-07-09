#pragma once
#include "Entity.h"
#include "SFML\Graphics.hpp"

class Brick 
	: public Entity
{
public:
	
	Brick(sf::Vector2f, sf::Vector2f);
	
	void SetHitPoints(int amount);
	int GetHitPoints();

	void SetColor(sf::Color);

	void OnCollisionEnter(Manifold) override;
	void OnCollisionStay(Manifold) override;
	void OnCollisionExit(Manifold) override;

protected:
	Collider * m_collider;
	SpriteRenderer * m_spriteRenderer;
	//ShapeRenderer * m_shapeRenderer;
	AudioSource * m_audioSource;

	int m_hitPoints = 1;

};

