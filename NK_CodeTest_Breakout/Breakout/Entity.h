#pragma once

#include "SFML\Graphics.hpp"
#include "Components.hpp"

class Component;
struct Manifold;

/*
	Entity  is the base object for any concrete implementation in the game
*/
class Entity
{

public:

	Entity(sf::Vector2f);
	virtual ~Entity() = default;

	virtual void Update(sf::Time&);
	virtual void Draw(sf::RenderWindow&);
	
	virtual void OnCollisionEnter(Manifold);
	virtual void OnCollisionStay(Manifold);
	virtual void OnCollisionExit(Manifold);

	virtual void OnTriggerEnter(Manifold);
	virtual void OnTriggerStay(Manifold);
	virtual void OnTriggerExit(Manifold);
	
	void SetPosition(sf::Vector2f);
	sf::Vector2f& GetPosition();

	template<typename T>
	T* GetComponent();

	template<typename T>
	T* AddComponent(Component*);

	virtual void CleanUp();

protected:

	sf::Vector2f m_position;

private:

	std::map<const type_info*, Component*> m_components;
};

template<typename T>
inline T* Entity::GetComponent()
{
	return static_cast<T*>(m_components[&typeid(T)]);
}

template<typename T>
inline T * Entity::AddComponent(Component * component)
{
	return static_cast<T*>(m_components[&typeid(T)] = component);
}