#pragma once
#include "ColliderComponent.h"

namespace viper {
	class CircleCollider2D : public ColliderComponent {
	public:
		float radius{ 0 };

	public:
		CLASS_PROTOTYPE(CircleCollider2D)

		void Update(float dt) override;
		bool CheckCollision(ColliderComponent& other) override;

		void Read(const json::value_t& value) override;
	};
}