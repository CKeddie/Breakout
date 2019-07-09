#include "PhysicsBody.h"
#include "Entity.h"
#include "SFMLMath.hpp"

PhysicsBody::PhysicsBody(Entity& holder)
	: Component::Component(holder)
{
}

sf::Vector2f& PhysicsBody::GetVelocity()
{
	return m_velocity;
}

sf::Vector2f & PhysicsBody::GetAcceleration()
{
	return m_acceleration;
}

void PhysicsBody::SetAcceleration(sf::Vector2f amount)
{
	m_acceleration = amount;
}

void PhysicsBody::AddAcceleration(sf::Vector2f amount)
{
	m_acceleration += amount;
}

void PhysicsBody::SetVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

void PhysicsBody::AddVelocity(sf::Vector2f amount)
{
	m_velocity += amount;
}

float PhysicsBody::GetFakeInertia()
{
	return m_fakeInertia;
}

void PhysicsBody::SetFakeInertia(float value)
{
	m_fakeInertia = value;
}

void PhysicsBody::SetMinVelocity(float mag)
{
	m_minVelocity = mag;
}

void PhysicsBody::SetMaxVelocity(float mag)
{
	m_maxVelocity = mag;
}

void PhysicsBody::Update(sf::Time & deltaTime)
{
	Entity& e = ((Entity&)m_entity);
	
	/*float length = sf::clamp(sf::getLength(m_velocity), m_minVelocity, m_maxVelocity);

	if (length > 0.1f)
		m_velocity = sf::getNormalized(m_velocity) * length;
	else
		m_velocity = sf::Vector2f();*/

	m_acceleration *= m_fakeInertia;
	m_velocity += m_acceleration;
	
	sf::Vector2f position = e.GetPosition();

	position += m_velocity * deltaTime.asSeconds();
	
	e.SetPosition(position);
}

void PhysicsBody::Draw(sf::RenderWindow &)
{
}
