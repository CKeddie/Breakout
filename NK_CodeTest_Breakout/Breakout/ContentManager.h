#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include <map>

/*
	Content management is responsible for loading and storing texture and font files
*/
class ContentManager
{
public:
	ContentManager();
	~ContentManager();

	sf::Font& GetFont(std::string name);
	sf::Texture& GetTexture(std::string name);


	void LoadFont(std::string filename, std::string storageID);
	void LoadTexture(std::string filename, std::string storageID);

	void CleanUp();

private:

	std::map<std::string, sf::Font*> m_fonts;
	std::map<std::string, sf::Texture*> m_textures;

};

