#include "UIHandler.h"

UIHandler::UIHandler()
	: m_font(nullptr)
{

}

UIHandler::~UIHandler()
{

}

void UIHandler::Update(sf::Time & deltaTime)
{
	for (int i = 0; i < m_uiElements.size(); i++)
	{
		if(m_uiElements[i]->GetActive())
			m_uiElements[i]->Update(deltaTime);
	}
}

void UIHandler::Draw(sf::RenderWindow & renderer)
{
	for (int i = 0; i < m_uiElements.size(); i++)
	{
		if(m_uiElements[i]->GetVisibility())
			m_uiElements[i]->Draw(renderer);
	}
}

void UIHandler::CleanUp()
{
	for (int i = 0; i < m_uiElements.size(); i++)
	{
		delete m_uiElements[i];
		m_uiElements[i] = nullptr;
	}

	m_uiElements.clear();
}


void UIHandler::SetFont(sf::Font & font)
{
	m_font = &font;
}

sf::Font & UIHandler::GetFont()
{
	return *m_font;
}

void UIHandler::AddUIElement(UIElement* element)
{
	element->SetFont(*m_font);
	m_uiElements.push_back(element);
}