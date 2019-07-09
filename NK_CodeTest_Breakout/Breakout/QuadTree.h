#pragma once

#include "SFML\Graphics.hpp"
#include "Collider.h"

/*
	Quad tree implementation for managing colliding bodies.
*/
class QuadTreeBroadphase
{
public:
	QuadTreeBroadphase(int capacity, sf::FloatRect&);
	virtual ~QuadTreeBroadphase() = default;

	void Insert(sf::Vector2f point, Collider & type);
	void Query(sf::Vector2f point, std::vector<Collider*> & potentialCollisions);
	void Query(sf::FloatRect, std::vector<Collider*> & potentialCollisions);
	void Remove(Collider & type, bool found = false);
	void ReInsert(Collider & type);
	void Draw(sf::RenderWindow & renderer);

	void CleanUp();

private:

	void Subdivide();
	
	int m_capacity;
	
	sf::FloatRect m_bounds;
	bool m_isSubDivided = false;
	bool m_debugMode = false;
	
	// safe to deallocate
	QuadTreeBroadphase * m_quads[4];

	// do not deallocate
	std::vector<Collider*> m_bucket;
};

