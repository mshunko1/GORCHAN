#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#pragma comment(lib,"sfml-audio.lib")


class audio_capture:public sf::SoundRecorder
{
public:
	virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
};

