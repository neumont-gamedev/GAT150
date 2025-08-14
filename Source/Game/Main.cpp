#include "Game/SpaceGame.h"

int main(int argc, char* argv[]) {
    viper::file::SetCurrentDirectory("Assets");
    viper::Logger::Info("current directory {}", viper::file::GetCurrentDirectory());

    // command-line arguments
    std::cout << argc << std::endl;
    for (int i = 0; i < argc; i++) {
        // c - string, read characters until '\0'
        viper::Logger::Debug("arg {}: {}", i, argv[i]);
    }

    // streams
    // console streams
    //std::cout << "hello, world" << " the story continues..." << std::endl;
    //int age{ 0 };
    //std::cout << "enter age: ";
    //if (!(std::cin >> age)) {
    //    std::cout << "invalid input\n";
    //}
    //std::cout << "you are " << (age * 365) << " days old.\n";

    // file streams
    std::fstream stream("test.txt");
    if (!stream) {
        std::cout << "could not open file.\n";
    }
    //std::cout << stream.rdbuf();
    std::string line;
    while (std::getline(stream, line)) {
        std::cout << line << std::endl;
    }

    // basic / built-in
    // int, float, double, bool, short, long

    // user data type streams
    // vec2, vec3, texture
    viper::vec3 v{ 34.5f, 65.5f, 54 };
    std::cout << v << std::endl;

    std::string vstr("{ 23.4, 76.3 }");
    std::stringstream sstream(vstr);

    viper::vec2 v2;
    sstream >> v2;

    std::cout << v2 << std::endl;

    // initialize engine
    viper::Logger::Warning("initialize engine...");
    viper::GetEngine().Initialize();

    // initialize game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    // initialize sounds
    viper::GetEngine().GetAudio().AddSound("bass.wav", "bass");
    viper::GetEngine().GetAudio().AddSound("snare.wav", "snare");
    viper::GetEngine().GetAudio().AddSound("clap.wav", "clap");
    viper::GetEngine().GetAudio().AddSound("close-hat.wav", "close-hat");
    viper::GetEngine().GetAudio().AddSound("open-hat.wav", "open-hat");

    SDL_Event e;
    bool quit = false;

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

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
