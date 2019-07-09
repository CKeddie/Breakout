#pragma once

#include "QuadTree.h"
#include "Manifold.hpp"

#include <stack>

/*
	Collision handler implements quad tree collision detection through 
	broadphase and narrowphase procedures to capture the pairs of colliding elements
	and resolving what happens to them respectively.
*/
class CollisionHandler
	: public QuadTreeBroadphase
{

public:
	CollisionHandler(int, sf::FloatRect);
	~CollisionHandler();

	void Broadphase(Collider *, std::vector<Collider*>);
	void NarrowPhase();


private:

	float IntervalDistance(float aMin, float aMax, float bMin, float bMax);
	
	std::stack<Manifold> m_manifolds;
};

