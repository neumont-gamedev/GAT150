#include "../GamePCH.h"
#include "Player.h"
#include "Rocket.h"
#include "SpaceGame.h"

FACTORY_REGISTER(Player)

void Player::Update(float dt)
{
    // particle system "flames"
    float angle = owner->transform.rotation + viper::random::getReal(-30.0f, 30.0f);
    viper::vec2 velocity = viper::vec2{ -1, 0 }.Rotate(viper::math::degToRad(angle));
    velocity *= viper::random::getReal(80.0f, 150.0f);

    viper::Particle particle;
    viper::vec2 offset = viper::vec2{ -40, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation));
    particle.position = owner->transform.position + offset;
    particle.velocity = velocity;
    particle.color = viper::vec3{ 1, 1, 0 };
    particle.lifespan = viper::random::getReal(0.5f, 1.0f);
    
    viper::GetEngine().GetPS().AddParticle(particle);

    // rotation
    float rotate = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

    owner->transform.rotation += (rotate * rotationRate) * dt;

    // thrust
    float thrust = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    viper::vec2 direction{ 1, 0 };
    viper::vec2 force = direction.Rotate(viper::math::degToRad(owner->transform.rotation)) * thrust * speed;
    auto* rb = owner->GetComponent<viper::RigidBody>();
    if (rb) {
        rb->velocity += force * dt;
    }

    owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());
    
    // check fire key pressed
    fireTimer -= dt;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0) {
        fireTimer = fireTime;

        // spawn rocket at object position and rotation
        viper::Transform transform{ owner->transform.position, owner->transform.rotation, 2.0f };
        auto rocket = viper::Instantiate("rocket", transform);
        // set rocket tag as player
        rocket->tag = "player";

        owner->scene->AddActor(std::move(rocket));
    }
}

void Player::OnCollision(viper::Actor* other) {
    if (owner->tag != other->tag) {
        owner->destroyed = true;

        EVENT_NOTIFY(player_dead);

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

void Player::Read(const viper::json::value_t& value) {
    Object::Read(value);

    JSON_READ(value, speed);
    JSON_READ(value, rotationRate);
    JSON_READ(value, fireTime);
}

