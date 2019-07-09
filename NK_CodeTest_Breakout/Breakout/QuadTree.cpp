#include "QuadTree.h"
#include "Entity.h"
#include <iostream>

QuadTreeBroadphase::QuadTreeBroadphase(int capacity, sf::FloatRect & bounds)
{
	// bucket capacity
	m_capacity = capacity;

	// area of the quad tree
	m_bounds = bounds;
}

void QuadTreeBroadphase::Insert(sf::Vector2f point, Collider & type)
{
	// check if the query point is in-bounds
	if (!m_bounds.contains(point))
		return;

	// if the bucket is not full
	if (m_bucket.size() < m_capacity)
	{
		// add element
		m_bucket.push_back(&type);
		return;
	}
	// generate subdivisions 
	else if (!m_isSubDivided)
		Subdivide();
	
	// insert through each subdivision
	if (m_isSubDivided)
	{
		for (auto& quad : m_quads)
		{
			quad->Insert(point, type);
		}		
	}	
}

void QuadTreeBroadphase::Query(sf::Vector2f point, std::vector<Collider*> & potentialCollisions)
{
	// return the bucket of the region that the point has successfully queried
	if (m_bounds.contains(point))
	{
		for (auto & it : m_bucket)
		{
			if (std::find(potentialCollisions.begin(), potentialCollisions.end(), it) == potentialCollisions.end())
			{
				potentialCollisions.push_back(it);
			}

		}

		if (m_isSubDivided)
		{
			for (auto& quad : m_quads)
			{
				quad->Query(point, potentialCollisions);			
			}
		}			
	}
}

void QuadTreeBroadphase::Query(sf::FloatRect area, std::vector<Collider*>& potentialCollisions)
{
	if (m_bounds.intersects(area))
	{
		// add each element to the set of potential collisions
		for (auto & it : m_bucket)
		{
			potentialCollisions.push_back(it);
			
		}

		// depth query for sub-regions
		if (m_isSubDivided)
		{
			for (auto& quad : m_quads)
			{
				quad->Query(area, potentialCollisions);
			}
		}
	}
}

void QuadTreeBroadphase::Remove(Collider & type, bool found)
{
	// find the index of the brick
	std::vector< Collider*>::iterator it = std::find(m_bucket.begin(), m_bucket.end(), &type);
	if (it != m_bucket.end())
	{
		found = true;
		int index = std::distance(m_bucket.begin(), it);
		// erase the reference in the bucket
		m_bucket.erase(m_bucket.begin() + index);
		// exit 
		return;
	}
	// brick not found
	else
	{
		// check for children
		if (m_isSubDivided)
		{
			bool childDeallocation = true;
			// recursively check and remove
			for (auto& quad : m_quads)
			{	
				if(!found)
					quad->Remove(type, found);				
				
				//check if child has no bits in bucket and no children
				childDeallocation &= (quad->m_bucket.size() == 0 && !quad->m_isSubDivided);
			}

			// child is ready to be deallocated
			if (childDeallocation)
			{
				for (auto & quad : m_quads)
					quad->CleanUp();

				// deallocate memory recursively
				for (auto & quad : m_quads)
				{
					delete quad;
					quad = nullptr;
				}

				m_isSubDivided = false;
			}
		}
		// element not found move on to bredth traversal
		else return;
	}

}

void QuadTreeBroadphase::ReInsert(Collider & type)
{
	// recursive remove
	Remove(type);

	// recursive insert
	Insert(type.GetEntity().GetPosition(), type);
}

void QuadTreeBroadphase::Draw(sf::RenderWindow & renderer)
{	
	//sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(m_bounds.width, m_bounds.height));
	//rect.setPosition(m_bounds.left, m_bounds.top);
	//rect.setFillColor(sf::Color::Transparent);
	//rect.setOutlineColor(sf::Color::Green);
	//rect.setOutlineThickness(5.0f);
	//renderer.draw(rect);

	if (!m_isSubDivided)
		return;

	for (auto & quad : m_quads)
		quad->Draw(renderer);
}

void QuadTreeBroadphase::CleanUp()
{
	// depth check children are present
	if (m_isSubDivided)
	{
		// deallocate memory recursively
		for (auto & quad : m_quads)
		{
			quad->CleanUp();

			delete quad;
			quad = nullptr;
		}
	}
}

void QuadTreeBroadphase::Subdivide()
{
	sf::FloatRect ne(m_bounds.left, m_bounds.top, m_bounds.width / 2, m_bounds.height / 2);
	m_quads[0] = new QuadTreeBroadphase(m_capacity, ne);

	sf::FloatRect nw(m_bounds.left + m_bounds.width / 2, m_bounds.top, m_bounds.width / 2, m_bounds.height / 2);
	m_quads[1] = new QuadTreeBroadphase(m_capacity, nw);

	sf::FloatRect se(m_bounds.left, m_bounds.top + m_bounds.height / 2, m_bounds.width / 2, m_bounds.height / 2);
	m_quads[2] = new QuadTreeBroadphase(m_capacity, se);

	sf::FloatRect sw(m_bounds.left + m_bounds.width / 2, m_bounds.top + m_bounds.height / 2, m_bounds.width / 2, m_bounds.height / 2);
	m_quads[3] = new QuadTreeBroadphase(m_capacity, sw);

	m_isSubDivided = true;
}