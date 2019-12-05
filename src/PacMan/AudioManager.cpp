#include "AudioManager.h"


AudioManager::AudioManager()
{
	//Initialize
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags) & mixFlags)) throw "Error: SDL_mixer init";

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw "Unable to init SDL_mixer audio systems";
	}

	LoadAudio(mtdl::AudioFile("main_theme", "../../res/au/mainTheme.mp3"));
}


AudioManager::~AudioManager()
{
	Mix_CloseAudio();
	Mix_Quit();
}


void AudioManager::LoadAudio(mtdl::AudioFile a) {
	Mix_Music *soundtrack{ Mix_LoadMUS(a.path.c_str()) };
	if (!soundtrack) throw "Unable to load the Mix_Music soundtrack";
	m_audioData[a.name] = soundtrack;
}

// MIX_MAX_VOLUME = 128
void AudioManager::StartAudio(std::string id, int vol, int loops) {
	Mix_VolumeMusic(vol);
	Mix_PlayMusic(m_audioData[id], loops);
	audioOn = true;
}

void AudioManager::PauseAudio() {
	Mix_PauseMusic();
	audioOn = false;
}

void AudioManager::ResumeAudio() {
	Mix_ResumeMusic();
	audioOn = true;
}

AudioManager* AudioManager::audio = nullptr;