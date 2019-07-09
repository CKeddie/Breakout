#include "AudioSource.h"
#include "Entity.h"
#include "AudioManager.h"

AudioSource::AudioSource(Entity& holder)
	: Component::Component(holder)
{

}

void AudioSource::SetVolume(std::string id, float volume)
{

	AudioManager::SetVolume(id, volume);
}

#include "AudioManager.h"
void AudioSource::LoadBuffer(sf::SoundBuffer & buffer)
{
	m_sounds.push_back(sf::Sound(buffer));
}

void AudioSource::PlayOneShot(std::string id)
{
	AudioManager::PlaySound(id);
}