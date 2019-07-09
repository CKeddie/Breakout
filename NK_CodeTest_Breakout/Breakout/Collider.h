#pragma once

#include "Component.h"
#include "ShapeRenderer.h"
#include <functional>

class Brick;
class Entity;


enum CollisionFlag
{
	NONE,
	REMOVE,
};

struct Manifold;

/*
	Collider component, for objects that should register collisions and responses
	key requirement for the collision system to work.
*/
class Collider :
	public ShapeRenderer
{
public:

	Collider(Entity&);
	
	sf::FloatRect GetBounds();
	
	void ResolveCollision(Manifold collider);
	void CalculateMinMax(sf::Vector2f normal, float & min, float & max);

	CollisionFlag GetFlags();
	void SetFlags(CollisionFlag);

	

private:

	CollisionFlag m_collisionFlag;

	bool m_isTrigger = false;
	bool m_isColliding = false, m_isCollidingOld = false;

};

