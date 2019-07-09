#include "Collider.h"
#include "Manifold.hpp"
#include "Entity.h"
#include "SFMLMath.hpp"

Collider::Collider(Entity & holder)
	: ShapeRenderer::ShapeRenderer(holder)
{

}

sf::FloatRect Collider::GetBounds()
{
	return m_drawShape->getGlobalBounds();
}


void Collider::ResolveCollision(Manifold other)
{
	m_isColliding = other.Collision;

	// collision has registered an entry
	if (m_isColliding && !m_isCollidingOld)
		if(m_isTrigger)
			m_entity.OnTriggerEnter(other);
		else 
			m_entity.OnCollisionEnter(other);
	// collision has registered a continuous collision
	else if (m_isColliding && m_isCollidingOld)
		if (m_isTrigger)
			m_entity.OnTriggerStay(other);
		else
			m_entity.OnCollisionStay(other);
	// collision has registered an exit
	else if (!m_isColliding && m_isCollidingOld)
		if (m_isTrigger)
			m_entity.OnTriggerExit(other);
		else
			m_entity.OnCollisionExit(other);

	m_isCollidingOld = m_isColliding;
}

void Collider::CalculateMinMax(sf::Vector2f normal, float & min, float & max)
{

	sf::Vector2f position = m_entity.GetPosition();
		
	sf::FloatRect rect = GetBounds();
	sf::Vector2f size(rect.width / 2, rect.height / 2);

	
	min = (position + (size * -1.f)) * normal;
	max = (position + (size * -1.f)) * normal;

	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			if (x == 0 || y == 0)
				continue;

			sf::Vector2f point = size;
			point.x *= x;
			point.y *= y;
			
			float dot = (position + point) * normal;

			if (dot < min)
				min = dot;
			else if (dot > max)
				max = dot;
		}
	}
}

CollisionFlag Collider::GetFlags()
{
	return m_collisionFlag;
}

void Collider::SetFlags(CollisionFlag flag)
{
	m_collisionFlag = flag;
}
