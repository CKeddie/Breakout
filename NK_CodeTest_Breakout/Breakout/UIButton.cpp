#include "UIButton.h"

#include "InputHandler.h"

UIButton::UIButton()
	: UIElement::UIElement()
{
	m_lable.SetText("Button");
}

void UIButton::Update(sf::Time & deltaTime)
{

	if (m_displaySprite.getGlobalBounds().contains(InputHandler::MousePosition()))
	{
		if (InputHandler::IsMouseButtonPressed(sf::Mouse::Button::Left))
		{
			m_displaySprite.setTexture(m_onButtonState[UIButtonState::Pressed]);
			if (m_function)
			{
				m_function();
				return;
			}
		}
		else
			m_displaySprite.setTexture(m_onButtonState[UIButtonState::Hover]);
	}
	else
		m_displaySprite.setTexture(m_onButtonState[UIButtonState::Released]);

	m_displaySprite.setPosition(m_position - ((sf::Vector2f)m_displaySprite.getTexture()->getSize() * .5f));

	m_lable.Update(deltaTime);
}

void UIButton::Draw(sf::RenderWindow & renderer)
{
	renderer.draw(m_displaySprite);
	m_lable.Draw(renderer);
}

void UIButton::SetPosition(sf::Vector2f position)
{
	UIElement::SetPosition(position);
	m_lable.SetPosition(position);	   
}

void UIButton::SetText(std::string text)
{
	m_lable.SetText(text);
}

void UIButton::LoadTexture(sf::Texture & texture, UIButtonState button)
{
	m_onButtonState[button] = texture;
	if (!m_displaySprite.getTexture())
		m_displaySprite.setTexture(texture);
}

void UIButton::LoadFunction(std::function<void(void)> function)
{
	m_function = function;
	//fun = function.target;
}

void UIButton::SetFont(sf::Font & font)
{
	UIElement::SetFont(font);
	m_lable.SetFont(font);
}

sf::Vector2f UIButton::GetSize()
{
	sf::FloatRect rect = m_displaySprite.getGlobalBounds();
	return sf::Vector2f(rect.width, rect.height);
}

void UIButton::CleanUp()
{
	m_lable.CleanUp();
}

