#pragma once
#include "../Math/Vector2.h"
#include <string>

struct SDL_Texture;

namespace viper {
	class Texture {
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, class Renderer& renderer);

		vec2 GetSize();

		friend class Renderer;

	private:
		SDL_Texture* m_texture{ nullptr };
	};
}
