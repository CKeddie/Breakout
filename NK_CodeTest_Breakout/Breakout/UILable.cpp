#include "UILable.h"



UILable::UILable()
	: UIElement::UIElement()
{
	m_active = true;
}

void UILable::Update(sf::Time & deltaTime)
{
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + (textRect.width * .5f), textRect.top + textRect.height * .5f);
}

void UILable::Draw(sf::RenderWindow & renderer)
{
	renderer.draw(m_text);
}

void UILable::SetText(std::string text)
{
	m_text.setString(text);
}

void UILable::SetFont(sf::Font & font)
{
	m_text.setFont(font);
}

void UILable::SetPosition(sf::Vector2f position)
{
	UIElement::SetPosition(position);
	m_text.setPosition(position);
}

void UILable::SetSize(const sf::Vector2f & size)
{
	m_text.setScale(size);
}
