#include "CollisionHandler.h"
#include "SFMLMath.hpp"
#include "Collider.h"
#include "Entity.h"

CollisionHandler::CollisionHandler(int cap, sf::FloatRect area)
	: QuadTreeBroadphase::QuadTreeBroadphase(cap, area)
{
}

CollisionHandler::~CollisionHandler()
{
}

void CollisionHandler::Broadphase(Collider * colliderA, std::vector<Collider*> potentialCollisions)
{
	for (auto & colliderB : potentialCollisions)
	{
		// get projections of A
		// vertical
		float aMinX = 0, aMaxX = 0;
		colliderA->CalculateMinMax(sf::Vector2f(1, 0), aMinX, aMaxX);
		// horizontal
		float aMinY = 0, aMaxY = 0;
		colliderA->CalculateMinMax(sf::Vector2f(0, 1), aMinY, aMaxY);

		// get projections of B
		// vertical
		float bMinX, bMaxX;
		colliderB->CalculateMinMax(sf::Vector2f(1, 0), bMinX, bMaxX);
		// horizontal
		float bMinY, bMaxY;
		colliderB->CalculateMinMax(sf::Vector2f(0, 1), bMinY, bMaxY);

		// check for an overlap on each axis
		float xOverlap = IntervalDistance(aMinX, aMaxX, bMinX, bMaxX);
		float yOverlap = IntervalDistance(aMinY, aMaxY, bMinY, bMaxY);

		// overlapping if both values are below zero
		bool isColliding = xOverlap < 0 && yOverlap < 0;

		// populate manifold
		Manifold manifold;

		manifold.ColliderA = colliderA;
		manifold.ColliderB = colliderB;
		manifold.Collision = isColliding;

		sf::Vector2f penDepth;
		
		// get direction of entities
		sf::Vector2f dir = colliderB->GetEntity().GetPosition() - colliderA->GetEntity().GetPosition();

		// selectively store the penetration depth depending on the side of approach

		// if the overlap is greater on the Y (coming from a side)
		if (std::abs(xOverlap) < std::abs(yOverlap))
			// if to the left
			if (dir.x < 0)
				// invert the x overlap amount (for correcting positions)
				penDepth.x = xOverlap = -xOverlap;
			else
				penDepth.x = xOverlap;
		else
			// if below
			if (dir.y < 0)
				penDepth.y = yOverlap = -yOverlap;
			else
				penDepth.y = yOverlap;

		manifold.PenetrationDepth = penDepth;

		// add manifold to the narrowphase
		m_manifolds.push(manifold);
	}
}

void CollisionHandler::NarrowPhase()
{// iterate through each potential collision
	std::vector<Collider*> removals;

	while (m_manifolds.size() > 0)
	{
		// get next manifold
		Manifold manifold = m_manifolds.top();
		
		// resolve collisions between colliders
		Collider * colliderA = manifold.ColliderA;
		Collider * colliderB = manifold.ColliderB;
		colliderA->ResolveCollision(manifold);
		
		// swap colliders so element B is always the opposing object
		manifold.ColliderA = colliderB;
		manifold.ColliderB = colliderA;
		colliderB->ResolveCollision(manifold);

		// if a removal has been flagged
		// add to a removals set
		if (colliderA->GetFlags() == REMOVE)
			removals.push_back(colliderA);
		if (colliderB->GetFlags() == REMOVE)
			removals.push_back(colliderB);

		// manifold has been consumed; pop off the stack
		m_manifolds.pop();
	}

	for (auto & collider : removals)
	{
		// remove all flagged items from removals
		Remove(*collider);
	}
}

float CollisionHandler::IntervalDistance(float aMin, float aMax, float bMin, float bMax)
{
	// determine if the projections of each min/max points on the colliders are either left or right
	// return B-A or A-B depending on direction
	return (aMin < bMin) ? bMin - aMax : aMin - bMax;
}