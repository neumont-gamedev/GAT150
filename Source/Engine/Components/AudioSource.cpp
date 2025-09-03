#include "AudioSource.h"
#include "Audio/AudioClip.h"
#include "Engine.h"

namespace viper {
	FACTORY_REGISTER(AudioSource)

	void AudioSource::Start() {
		if (!audioClipName.empty()) {
			audioClip = Resources().Get<AudioClip>(audioClipName, GetEngine().GetAudio());
			ASSERT(audioClip);

			if (playOnStart) {
				Play();
			}
		}
	}

	void AudioSource::Update(float dt) {
		//
	}

	void AudioSource::Play() {
		if (audioClip) {
			GetEngine().GetAudio().PlaySound(*audioClip);
		}
	}

	void AudioSource::Read(const json::value_t& value) {
		JSON_READ(value, audioClipName);
		JSON_READ(value, playOnStart);
	}
}
