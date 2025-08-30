#include "EnginePCH.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Engine.h"

namespace viper {
	FACTORY_REGISTER(SpriteRenderer)

	void SpriteRenderer::Start() {
		// get texture resource if texture doesn't exist and there's a texture name
		if (!texture && !textureName.empty()) {
			texture = Resources().Get<Texture>(textureName, GetEngine().GetRenderer());
		}
	}

	void SpriteRenderer::Update(float dt) {
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer) {
		if (texture) {
			if (textureRect.w > 0 && textureRect.h > 0) {
				renderer.DrawTexture(*texture,
					textureRect,
					owner->transform.position.x,
					owner->transform.position.y,
					owner->transform.rotation,
					owner->transform.scale);
			} else {
				renderer.DrawTexture(*texture,
					owner->transform.position.x,
					owner->transform.position.y,
					owner->transform.rotation,
					owner->transform.scale);
			}
		}
	}

	void SpriteRenderer::Read(const json::value_t& value) {
		Object::Read(value);

		JSON_READ_NAME(value, "texture_name", textureName);
	}
}
