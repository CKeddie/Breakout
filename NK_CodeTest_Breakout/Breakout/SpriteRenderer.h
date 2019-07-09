#pragma once
#include "Component.h"

class SpriteRenderer :
	public Component
{
public:
	SpriteRenderer(Entity&);

	void Update(sf::Time&)override;
	void Draw(sf::RenderWindow&)override;

	void SetColor(sf::Color color);
	sf::Color GetColor();
	void LoadSprite(sf::Sprite&);
	void CleanUp();
	
protected:
	
	sf::Sprite * m_sprite;

};

