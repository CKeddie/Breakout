#include "Paddle.h"
#include "Application.h"
#include "InputHandler.h"
#include "SFML\System\Vector2.hpp"
#include "SFMLMath.hpp"
#include <cmath>
#include "Manifold.hpp"

Paddle::Paddle(sf::Vector2f pos, sf::Vector2f size)
	: Entity::Entity(pos)
{
	m_physicsBody = AddComponent<PhysicsBody>(new PhysicsBody(*this));
	m_physicsBody->SetMinVelocity(0);
	m_physicsBody->SetFakeInertia(0.25f);

	m_spriteRenderer = AddComponent<SpriteRenderer>(new SpriteRenderer(*this));

	m_collider = AddComponent<Collider>(new Collider(*this));
	sf::Shape* shape = new sf::RectangleShape(size);
	shape->setPosition(pos);
	m_collider->LoadShape(*shape);
	m_collider->SetColor(sf::Color::Blue);

}

void Paddle::Move(float x)
{
	m_physicsBody->AddAcceleration(sf::Vector2f(x, 0));

}

void Paddle::Update(sf::Time & deltaTime)
{
	Entity::Update(deltaTime);
	m_physicsBody->SetVelocity(m_physicsBody->GetVelocity() * 0.99f);
}

void Paddle::Draw(sf::RenderWindow & renderer)
{
	Entity::Draw(renderer);
}

void Paddle::OnCollisionEnter(Manifold manifold)
{
	AudioManager::SetVolume("bubble", 10);
	AudioManager::PlaySound("bubble");
}

void Paddle::OnCollisionStay(Manifold)
{
}

void Paddle::OnCollisionExit(Manifold)
{
}

