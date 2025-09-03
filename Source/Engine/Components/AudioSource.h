#pragma once
#include "Framework/Component.h"

namespace viper {
	class AudioSource : public Component {
	public:
		std::string audioClipName;
		bool playOnStart{ false };

		res_t<class AudioClip> audioClip;

	public:
		CLASS_PROTOTYPE(AudioSource)

		void Start() override;
		void Update(float dt) override;
		void Play();

		void Read(const json::value_t& value) override;
	};
}