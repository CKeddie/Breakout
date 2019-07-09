#include "ShapeRenderer.h"
#include "Entity.h"

ShapeRenderer::ShapeRenderer(Entity & holder)
	: Component::Component(holder)
{
}

void ShapeRenderer::Update(sf::Time &)
{
	if (m_drawShape)
	{
		sf::Vector2f centerAligned;
		sf::CircleShape * circle = dynamic_cast<sf::CircleShape*>(m_drawShape);
		sf::RectangleShape * rect = dynamic_cast<sf::RectangleShape*>(m_drawShape);
		
		// shift shape position to be center to m_position
		if (circle)
		{
			float r = circle->getRadius();
			centerAligned = sf::Vector2f(r, r);
		}
		else if (rect)
		{
			centerAligned = rect->getSize() * 0.5f;
		}

		m_drawShape->setPosition(m_entity.GetPosition() - centerAligned);
	}
}

void ShapeRenderer::Draw(sf::RenderWindow & renderer)
{
	if (m_drawShape)
	{
		//renderer.draw(*m_drawShape);
	}
}

void ShapeRenderer::LoadShape(sf::Shape & shape)
{
	m_drawShape = &shape;
}

void ShapeRenderer::SetColor(sf::Color color)
{
	m_drawShape->setFillColor(color);
}

sf::Color ShapeRenderer::GetColor()
{
	return m_drawShape->getFillColor();
}

void ShapeRenderer::CleanUp()
{
	Component::CleanUp();

	delete m_drawShape;
	m_drawShape = nullptr;
}