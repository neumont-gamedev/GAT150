#include "FlyingEnemyController.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start() {
	m_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void FlyingEnemyController::Update(float dt) {

	// move towards player
	auto player = owner->scene->GetActorByName<viper::Actor>("platformplayer");
	if (player) {
		viper::vec2 direction = player->transform.position - owner->transform.position;
		m_rigidBody->ApplyForce(direction.Normalized() * speed);
		//if (player->transform.position.x < owner->transform.position.x) dir = -1;
		//else dir = 1;
	}

	//if (dir != 0) {
	//	m_rigidBody->ApplyForce(viper::vec2{ 1, 0 } *dir * 500);
	//}
}

void FlyingEnemyController::OnCollision(viper::Actor* other) {
}

void FlyingEnemyController::Read(const viper::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}
