#include "Game/SpaceGame.h"

class A {
public:
    A() = default;
    A(int size) : size{ size } 
    {
        buffer = new int[size];
        for (int i = 0; i < size; i++) buffer[i] = i;
    }
    A(const A& other) : 
        size{ other.size }
    {
        buffer = new int[other.size];
        for (int i = 0; i < size; i++) buffer[i] = i;
    }
    A& operator = (const A& other) 
    { 
        size = other.size;
        buffer = other.buffer;
        return *this;
    }
    ~A() = default;
        
public:
    int size{ 0 };
    int* buffer{ nullptr };
};


int main(int argc, char* argv[]) {
    /*
    A a1{ 4 };
    std::cout << a1.size << std::endl;
    std::cout << a1.buffer[2] << std::endl;

    A a2{ a1 }; // copy constructor

    a1.buffer[2] = 45;

    std::cout << a2.size << std::endl;
    std::cout << a2.buffer[2] << std::endl;

    A a3;
    a3 = a1; // assignment operator
    std::cout << a3.size << std::endl;
    */

    viper::file::SetCurrentDirectory("Assets");
    viper::Logger::Info("current directory {}", viper::file::GetCurrentDirectory());

    // initialize engine
    viper::Logger::Info("initialize engine...");
    viper::GetEngine().Initialize();

    // initialize game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    SDL_Event e;
    bool quit = false;

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // update
        viper::GetEngine().Update();
        game->Update(viper::GetEngine().GetTime().GetDeltaTime());

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // draw
        viper::vec3 color{ 0, 0, 0 };
        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

        game->Draw(viper::GetEngine().GetRenderer());

        viper::GetEngine().GetRenderer().Present();
    }

    game->Shutdown();
    game.release();
    viper::GetEngine().Shutdown();

    return 0;
}
