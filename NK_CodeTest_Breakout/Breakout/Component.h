#pragma once

#include "SFML\Graphics.hpp"

class Entity;
/*
	component-based composition system that allows scripts to be attached to entities
	for additional functionality
*/
class Component
{
public:

	Component(Entity&);
	virtual ~Component() = default;

	virtual void Update(sf::Time&);
	virtual void Draw(sf::RenderWindow&);
	
	Entity& GetEntity();

	virtual void CleanUp();

protected:

	Entity & m_entity;
};