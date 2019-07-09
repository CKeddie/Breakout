#include "ContentManager.h"
#include <iostream>


ContentManager::ContentManager()
{

}

ContentManager::~ContentManager()
{

}

sf::Font & ContentManager::GetFont(std::string name)
{
	return *m_fonts[name];
}

sf::Texture & ContentManager::GetTexture(std::string name)
{
	return *m_textures[name];
}

//sf::SoundBuffer & ContentManager::GetSound(std::string name)
//{
//	return *m_sounds[name];
//}

void ContentManager::LoadFont(std::string filename, std::string storageID)
{
	sf::Font * font = new sf::Font();
	std::string path = "Content/Fonts/";
	if (font->loadFromFile(path + filename))
	{
		m_fonts[storageID] = font;
		std::cout << "successfully loaded: " << path + filename << std::endl;
	}
	else
		std::cout << "failed to load: " << path + filename << std::endl;

}

void ContentManager::LoadTexture(std::string filename, std::string storageID)
{
	sf::Texture* tex = new sf::Texture();
	std::string path = "Content/Textures/";
	if (tex->loadFromFile(path + filename))
	{
		m_textures[storageID] = tex;
		std::cout << "successfully loaded: " << path + filename << std::endl;
	}
	else
		std::cout << "failed to load: " << path + filename << std::endl;

}

//void ContentManager::LoadSound(std::string filename, std::string storageID)
//{	
//	sf::SoundBuffer * sound = new sf::SoundBuffer();
//	std::string path = "Content/SFX/";
//	if (sound->loadFromFile(path + filename))
//	{
//		m_sounds[storageID] = sound;
//		std::cout << "successfully loaded: " << path + filename << std::endl;		
//	}
//	else
//		std::cout << "failed to load: " << path + filename << std::endl;	
//}

void ContentManager::CleanUp()
{
	std::map<std::string, sf::Font*>::iterator fontIt;
	for (fontIt = m_fonts.begin(); fontIt != m_fonts.end(); ++fontIt)
	{
		sf::Font * font = fontIt->second;
		delete font;
		font = nullptr;
	}
	m_fonts.clear();

	std::map<std::string, sf::Texture*>::iterator texIt;
	for (texIt = m_textures.begin(); texIt != m_textures.end(); ++texIt)
	{
		sf::Texture * texture = texIt->second;
		delete texture;
		texture = nullptr;
	}
	m_textures.clear();
}