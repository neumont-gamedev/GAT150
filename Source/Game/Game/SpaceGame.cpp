#include "../GamePCH.h"
#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

bool SpaceGame::Initialize()
{
    OBSERVER_ADD(player_dead);
    OBSERVER_ADD(add_points);

    m_scene = std::make_unique<viper::Scene>(this);
    m_scene->Load("scene.json");

    m_titleText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("title_font", "arcadeclassic.ttf", 128.0f));
    m_scoreText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "arcadeclassic.ttf", 48.0f));
    m_livesText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "arcadeclassic.ttf", 48.0f));

    return true;
}

void SpaceGame::Shutdown() {
    //
}

void SpaceGame::Update(float dt)
{
    switch (m_gameState)
    {
    case SpaceGame::GameState::Initialize:
        m_gameState = GameState::Title;
        break;

    case SpaceGame::GameState::Title:
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
        }
        break;

    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_gameState = GameState::StartRound;
        break;

    case SpaceGame::GameState::StartRound:
    {
        m_scene->RemoveAllActors();

        auto player = viper::Instantiate("player");
        m_scene->AddActor(std::move(player));

        m_gameState = GameState::Game;
    }
        break;
    case SpaceGame::GameState::Game:
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = 5;
            SpawnEnemy();
        }

        break;
    case SpaceGame::GameState::PlayerDead:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_lives--;
            if (m_lives == 0) {
                m_gameState = GameState::GameOver;
                m_stateTimer = 3;
            }
            else {
                m_gameState = GameState::StartRound;
            }
        }
        break;
    case SpaceGame::GameState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_gameState = GameState::Title;
        }
        break;
    default:
        break;
    }

    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q)) {
        viper::GetEngine().GetTime().SetTimeScale(0.15f);
    }
    else {
        viper::GetEngine().GetTime().SetTimeScale(1.0f);
    }

    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(viper::Renderer& renderer) {
    m_scene->Draw(renderer);

    if (m_gameState == GameState::Title) {
        m_titleText->Create(renderer, "PIT VIPER", viper::vec3{ 1, 0, 0 });
        m_titleText->Draw(renderer, 400, 400);
    }
    if (m_gameState == GameState::GameOver) {
        m_titleText->Create(renderer, "GAME OVER", viper::vec3{ 1, 0, 0 });
        m_titleText->Draw(renderer, 400, 400);
    }

    m_scoreText->Create(renderer, "SCORE  " + std::to_string(m_score), { 1, 1, 1 });
    m_scoreText->Draw(renderer, 20, 20);

    m_livesText->Create(renderer, "LIVES  " + std::to_string(m_lives), {1, 1, 1});
    m_livesText->Draw(renderer, (float)(renderer.GetWidth() - 200), (float)20);

    viper::GetEngine().GetPS().Draw(renderer);
}


void SpaceGame::OnNotify(const viper::Event& event) {
    if (viper::equalsIgnoreCase(event.id, "player_dead")) {
        OnPlayerDeath();
    }
    else if (viper::equalsIgnoreCase(event.id, "add_points")) {
        AddPoints(std::get<int>(event.data));
    }
}

void SpaceGame::OnPlayerDeath() {
    m_gameState = GameState::PlayerDead;
    m_stateTimer = 2;
}

void SpaceGame::SpawnEnemy() {
    // get player actor
    viper::Actor* player = m_scene->GetActorByName<viper::Actor>("player");
    if (player) {
        // spawn at random position away from player
        viper::vec2 position = player->transform.position + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
        viper::Transform transform{ position, viper::random::getReal(0.0f, 360.0f), 2.0f };

        auto enemy = viper::Instantiate("enemy", transform);
        m_scene->AddActor(std::move(enemy));
    }
}

