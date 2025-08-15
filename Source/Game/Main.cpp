#include "Game/SpaceGame.h"

int main(int argc, char* argv[]) {
    viper::file::SetCurrentDirectory("Assets");
    viper::Logger::Info("current directory {}", viper::file::GetCurrentDirectory());

    // !! this code is not neccessary, it just shows the contents of the file !!
    std::string buffer;
    viper::file::ReadTextFile("json.txt", buffer);
    // show the contents of the json file
    std::cout << buffer << std::endl;

    // create json document from the json file contents
    rapidjson::Document document;
    viper::json::Load("json.txt", document);

    /*
    // read the age data from the json
    int age;
    viper::json::Read(document, "age", age);
    // show the age data
    std::cout << age << std::endl;

    bool isAwake;
    viper::json::Read(document, "isAwake", isAwake);
    // show the isAwake data
    //std::cout << isAwake << std::endl;

    viper::vec2 position;
    JSON_READ(document, position);
    //viper::json::Read(document, "position", position);
    std::cout << position.x << " " << position.y << std::endl;
    */

    std::string name;
    int age;
    float speed;
    bool isAwake;
    viper::vec2 position;
    viper::vec3 color;

    //viper::json::Read(document, "name", name);
    //viper::json::Read(document, "age", age);
    //viper::json::Read(document, "speed", speed);
    //viper::json::Read(document, "isAwake", isAwake);
    //viper::json::Read(document, "position", position);
    //viper::json::Read(document, "color", color);

    JSON_READ(document, name);
    JSON_READ(document, age);
    JSON_READ(document, speed);
    JSON_READ(document, isAwake);
    JSON_READ(document, position);
    JSON_READ(document, color);

    // show the data
    std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
    std::cout << position.x << " " << position.y << std::endl;
    std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;

    /*
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
    */

    return 0;

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
