#include "../GamePCH.h"
#include "Rocket.h"
#include "Engine.h"
#include "Player.h"

FACTORY_REGISTER(Rocket)

void Rocket::Update(float dt) {
    // move rocket
    viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation)) * speed;
    auto rb = owner->GetComponent<viper::RigidBody>();
    if (rb) {
        rb->SetVelocity(force);
    }

    owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    // particle system "flames"
    float angle = owner->transform.rotation + viper::random::getReal(-60.0f, 60.0f);
    viper::vec2 velocity = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(angle));
    velocity *= viper::random::getReal(80.0f, 150.0f);

    viper::Particle particle;
    particle.position = owner->transform.position;
    particle.velocity = velocity;
    particle.color = (owner->tag == "enemy") ? viper::vec3{ 0, 1, 1 } : viper::vec3{ 1, 1, 0 };
    particle.lifespan = viper::random::getReal(0.15f, 0.3f);

    viper::GetEngine().GetPS().AddParticle(particle);
}

void Rocket::OnCollision(viper::Actor* other) {
    if (owner->tag != other->tag) {
        owner->destroyed = true;
    }
}

void Rocket::Read(const viper::json::value_t& value) {
    Object::Read(value);

    JSON_READ(value, speed);
}
