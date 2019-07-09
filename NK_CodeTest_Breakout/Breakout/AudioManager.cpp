#include "AudioManager.h"

AudioManager * AudioManager::s_instance = nullptr;

//sf::SoundBuffer & AudioManager::GetBuffer(std::string name)
//{
//	return m_soundBuffers[name];
//}

// load the buffer from file
void AudioManager::LoadBuffer(std::string filename, std::string name)
{
	std::string path = "Content/SFX/";
	sf::SoundBuffer buffer;
	if (Instance()->m_soundBuffers[name].loadFromFile(path + filename))
	{ 
		std::cout << "Successfully loaded " << name << " at path: " << path << std::endl;
		Instance()->m_sounds[name] = sf::Sound();
		Instance()->m_sounds[name].setBuffer(Instance()->m_soundBuffers[name]);
	}
	else
	{
		std::cout << "Could not load file: " << name << " at path: " << path << std::endl;
	}

}


// stream music file
void AudioManager::PlayMusic(std::string filename)
{
	std::string path = "Content/Music/";

	if (!Instance()->m_music.openFromFile(path + filename))
	{
		std::cout << "error with music file" << std::endl;
	}
	
	Instance()->m_music.play();
	Instance()->m_music.setLoop(true);
	Instance()->m_music.setVolume(10);
}


void AudioManager::StopMusic()
{
	Instance()->m_music.stop();
}

void AudioManager::PlaySound(std::string id)
{
	sf::Sound & sound = Instance()->m_sounds[id];
	sound.play();
}

void AudioManager::SetVolume(std::string id, int volume)
{
	Instance()->m_sounds[id].setVolume(volume);
}