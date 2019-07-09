#include "Entity.h"
#include "Manifold.hpp"

Entity::Entity(sf::Vector2f position = sf::Vector2f())
{
	SetPosition(position);
}

void Entity::Update(sf::Time & deltaTime)
{
	for (auto & component : m_components)
		component.second->Update(deltaTime);
}

void Entity::Draw(sf::RenderWindow & renderer)
{
	for (auto & component : m_components)
		component.second->Draw(renderer);
}

void Entity::OnCollisionEnter(Manifold manifold)
{
}

void Entity::OnCollisionStay(Manifold)
{
}

void Entity::OnCollisionExit(Manifold)
{
}

void Entity::OnTriggerEnter(Manifold)
{
}

void Entity::OnTriggerStay(Manifold)
{
}

void Entity::OnTriggerExit(Manifold)
{
}

void Entity::SetPosition(sf::Vector2f position)
{
	m_position = position;
}

sf::Vector2f & Entity::GetPosition()
{
	return m_position;
}

void Entity::CleanUp()
{
	for (auto & c : m_components)
	{
		Component * component = c.second;

		component->CleanUp();
		
		delete component;
		component = nullptr;
	}
	m_components.clear();
}
