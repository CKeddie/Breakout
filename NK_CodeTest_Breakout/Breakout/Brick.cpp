#include "Brick.h"
#include "Manifold.hpp"

Brick::Brick(sf::Vector2f size, sf::Vector2f position)
	: Entity::Entity(position)
{
	//m_position = position;
	m_collider = AddComponent<Collider>(new Collider(*this));
	m_audioSource = AddComponent<AudioSource>(new AudioSource(*this));

	sf::Shape * shape = new sf::RectangleShape(size);
	m_collider->LoadShape(*shape);	
	m_spriteRenderer = AddComponent<SpriteRenderer>(new SpriteRenderer(*this));
}

void Brick::SetHitPoints(int amount)
{
	m_hitPoints = amount;
}

int Brick::GetHitPoints()
{
	return m_hitPoints;
}

void Brick::SetColor(sf::Color color)
{
	m_collider->SetColor(color);
}

void Brick::OnCollisionEnter(Manifold manifold)
{
	m_hitPoints--;
	m_audioSource->SetVolume("deflect", 10);
	m_audioSource->PlayOneShot("deflect");
	if (m_hitPoints <= 0)
	{
		m_collider->SetFlags(REMOVE);
		m_audioSource->SetVolume("death", 10);
		m_audioSource->PlayOneShot("death");
	}
}

void Brick::OnCollisionStay(Manifold)
{
}

void Brick::OnCollisionExit(Manifold)
{
}
