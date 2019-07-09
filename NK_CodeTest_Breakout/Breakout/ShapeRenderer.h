#pragma once
#include "Component.h"

class Entity;

/*
	basic renderer/wrapper for shapes in sfml
*/
class ShapeRenderer :
	public Component
{
public:

	ShapeRenderer(Entity &);
	void Update(sf::Time&)override;
	void Draw(sf::RenderWindow&)override;
	virtual void LoadShape(sf::Shape&);
	void SetColor(sf::Color color);
	sf::Color GetColor();
	void CleanUp()override;
	

protected:

	sf::Shape* m_drawShape;
};

