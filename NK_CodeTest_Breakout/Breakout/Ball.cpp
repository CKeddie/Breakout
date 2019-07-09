#include "Ball.h"
#include "Components.hpp"
#include "SFMLMath.hpp"
#include "Manifold.hpp"
#include "Entity.h"
#include "Paddle.h"
#include "Brick.h"
Ball::Ball(sf::Vector2f position, float radius, int resolution)
	: Entity::Entity(position)
{
	m_radius = radius;
	m_resolution = resolution;

	m_physicsBody = AddComponent<PhysicsBody>(new PhysicsBody(*this));
	
	m_collider = AddComponent<Collider>(new Collider(*this));
	sf::Shape * shape = new sf::CircleShape(radius, resolution);
	m_collider->LoadShape(*shape);
	m_collider->SetColor(sf::Color::Red);

	m_audioSource = AddComponent<AudioSource>(new AudioSource(*this));

	m_spriteRenderer = AddComponent<SpriteRenderer>(new SpriteRenderer(*this));
}

void Ball::OnCollisionEnter(Manifold manifold)
{
	sf::Vector2f velocity = m_physicsBody->GetVelocity();
	sf::Vector2f p0 = GetPosition();
	Collider * colliderB = manifold.ColliderB;

	Entity & b = colliderB->GetEntity();
	sf::Vector2f p1 = b.GetPosition();

	sf::Vector2f n = (velocity);

	float speed = 10;

	if (typeid(b) == typeid(Brick))
	{
		sf::Color color = b.GetComponent<SpriteRenderer>()->GetColor();
		m_spriteRenderer->SetColor(color);
	}

	if (std::abs(manifold.PenetrationDepth.x) > std::abs(manifold.PenetrationDepth.y))
	{
		velocity.x *= -1;
	}
	else
	{
		velocity.y *= -1;
	}

	SetPosition(p0 + manifold.PenetrationDepth);
	// set new velocity
	m_physicsBody->SetVelocity(velocity);
	m_audioSource->SetVolume("bounce", 10);
	m_audioSource->PlayOneShot("bounce");

}

void Ball::OnCollisionStay(Manifold manifold)
{

}

void Ball::OnCollisionExit(Manifold manifold)
{

}

void Ball::SetColor(sf::Color color)
{
	m_collider->SetColor(color);
}