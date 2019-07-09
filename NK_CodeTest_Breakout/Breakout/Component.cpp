#include "Component.h"
#include "Entity.h"

Component::Component(Entity& holder)
	: m_entity(holder)
{

}

void Component::CleanUp()
{

}

void Component::Update(sf::Time &)
{
}

void Component::Draw(sf::RenderWindow &)
{
}

Entity & Component::GetEntity()
{
	return m_entity;
}

