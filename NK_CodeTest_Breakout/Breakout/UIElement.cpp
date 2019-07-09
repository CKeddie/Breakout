#include "UIElement.h"


UIElement::UIElement()
{
}

sf::Vector2f UIElement::GetPosition()
{
	return m_position;
}

void UIElement::SetPosition(sf::Vector2f pos)
{
	m_position = pos;
}

void UIElement::SetActive(bool state)
{
	m_active = state;
}

bool UIElement::GetActive()
{
	return m_active;
}

void UIElement::SetVisibility(bool state)
{
	m_visibility = state;
}

bool UIElement::GetVisibility()
{
	return m_visibility;
}

void UIElement::SetFont(sf::Font & font)
{
	m_font = &font;
}

void UIElement::CleanUp()
{

}
