#pragma once
#include "Component.h"
#include "SFML\Audio.hpp"

/*
	Audio component for adding audio functionality to entities
	edit: originally instantiated played a stored sound however
	multiple instances caused errors in openAL where the number of sounds 
	exceeded the number of available channels. All sounds are now
	centralised to an audio manager
	
*/
class AudioSource :
	public Component
{
public:
	AudioSource(Entity &);

	void LoadBuffer(sf::SoundBuffer&); // deprecated
	void SetVolume(std::string id, float volume);
	void PlayOneShot(std::string id);
	
private:

	std::vector<sf::Sound> m_sounds; // deprecated
	
};

