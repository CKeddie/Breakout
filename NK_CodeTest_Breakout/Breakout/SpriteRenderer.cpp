#include "SpriteRenderer.h"

#include "Entity.h"

SpriteRenderer::SpriteRenderer(Entity& holder)
	: Component::Component(holder)
{
}

void SpriteRenderer::Update(sf::Time & deltTime)
{
	if(m_sprite)
		m_sprite->setPosition(m_entity.GetPosition());
}

void SpriteRenderer::Draw(sf::RenderWindow & renderer)
{
	
	if (m_sprite)
	{
		float x = m_sprite->getGlobalBounds().width / 2;
		float y = m_sprite->getGlobalBounds().height / 2;
		m_sprite->setPosition(m_entity.GetPosition() - sf::Vector2f(x, y));
		renderer.draw(*m_sprite);
	}
}

void SpriteRenderer::SetColor(sf::Color color)
{
	m_sprite->setColor(color);
}

sf::Color SpriteRenderer::GetColor()
{
	return m_sprite->getColor();
}

void SpriteRenderer::LoadSprite(sf::Sprite & sprite)
{
	CleanUp();
	m_sprite = new sf::Sprite(sprite);
}

void SpriteRenderer::CleanUp()
{
	Component::CleanUp();
	if (m_sprite)
	{
		delete m_sprite;
		m_sprite = nullptr;
	}
}
