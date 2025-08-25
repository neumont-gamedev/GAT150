#include "../GamePCH.h"
#include "Enemy.h"
#include "Player.h"
#include "Rocket.h"

FACTORY_REGISTER(Enemy)

void Enemy::Start() {
    m_rigidBody = owner->GetComponent<viper::RigidBody>();
    fireTimer = fireTime;
}

void Enemy::Update(float dt) {
    // check if player seen (player in scene && < angle)
    bool playerSeen = false;
    auto player = owner->scene->GetActorByName<viper::Actor>("player");
    if (player) {
        viper::vec2 direction{ 0, 0 };
        direction = player->transform.position - owner->transform.position;

        direction = direction.Normalized();
        viper::vec2 forward = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation));

        float angle = viper::math::radToDeg(viper::vec2::AngleBetween(forward, direction));
        playerSeen = angle <= 30;

        // rotates toward player if seen
        if (playerSeen) {
            float angle = viper::vec2::SignedAngleBetween(forward, direction);
            angle = viper::math::sign(angle);
            owner->transform.rotation += viper::math::radToDeg(angle * 5 * dt);
        }
    }

    // move enemy
    viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation)) * speed;
    if (m_rigidBody) {
        m_rigidBody->velocity += force * dt;
    }

    owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    // check fire
    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireTime;

        // spawn rocket at actor position and rotation
        viper::Transform transform{ owner->transform.position, owner->transform.rotation, 2.0f };
        auto rocket = viper::Instantiate("rocket", transform);
        // set rocket tag as enemy
        rocket->tag = "enemy";

        owner->scene->AddActor(std::move(rocket));
    }
}

void Enemy::OnCollision(viper::Actor* other)
{
    if (owner->tag != other->tag) {
        owner->destroyed = true;
        owner->scene->GetGame()->AddPoints(100);
        // particle system explosion
        for (int i = 0; i < 100; i++) {
            viper::Particle particle;
            particle.position = owner->transform.position;
            particle.velocity = viper::random::onUnitCircle() * viper::random::getReal(10.0f, 200.0f);
            particle.color = viper::vec3{ 1, 1, 1 };
            particle.lifespan = 2;

            viper::GetEngine().GetPS().AddParticle(particle);
        }
    }
}

void Enemy::Read(const viper::json::value_t& value) {
    Object::Read(value);

    JSON_READ(value, speed);
    JSON_READ(value, fireTime);
}
