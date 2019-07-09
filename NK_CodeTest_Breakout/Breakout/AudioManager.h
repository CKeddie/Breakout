#pragma once

#include <SFML\Audio.hpp>
#include <map>
#include <iostream>

/*
	Audiomanager is responsible for content management of audio files and streaming music files
*/
class AudioManager final
{
public:
	static AudioManager * Instance()
	{
		if (s_instance == nullptr)
			s_instance = new AudioManager();

		return s_instance;
	}

	//sf::SoundBuffer & GetBuffer(std::string);
	static void LoadBuffer(std::string, std::string);

	static void PlayMusic(std::string);
	static void StopMusic();

	static void PlaySound(std::string id);
	static void SetVolume(std::string id, int volume);
	
private:
	static AudioManager * s_instance;

	sf::Music m_music;

	std::map<std::string, sf::SoundBuffer> m_soundBuffers;
	std::map<std::string, sf::Sound> m_sounds;

};

