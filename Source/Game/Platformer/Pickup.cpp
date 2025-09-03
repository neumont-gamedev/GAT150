#include "Pickup.h"

FACTORY_REGISTER(Pickup)

void Pickup::Start() {
	m_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void Pickup::Update(float dt) {
	//
}

void Pickup::OnCollision(viper::Actor* other) {
	if (viper::equalsIgnoreCase(other->tag, "player")) {
		owner->destroyed = true;
	}
}

void Pickup::Read(const viper::json::value_t& value) {
	Object::Read(value);
}
