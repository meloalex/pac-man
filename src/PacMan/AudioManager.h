#pragma once
#include <SDL_mixer.h>
#include <unordered_map>
#include "../mtdl/mtdl.h"

class AudioManager
{
private:
	static AudioManager *audio;
	std::unordered_map<std::string, Mix_Music*> m_audioData;
	AudioManager();
public:
	bool audioOn;
	bool audioStarted;

	static AudioManager *Instance()
	{
		if (audio == nullptr) { audio = new AudioManager; }
		return audio;
	};

	~AudioManager();
	void LoadAudio(mtdl::AudioFile a);
	void PauseAudio();
	void ResumeAudio();
	void StartAudio(std::string id, int vol, int loops);
};

