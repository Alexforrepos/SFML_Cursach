// Game.h
#pragma once
#include "./Utils/Config.h"
#include "./../Interfaces/I_Serialize.h"
#include "./GameManagers/GameProcess.h"
#include "./../Engine/R_Manager.h"
#include "./../Engine/O_Manager.h"
#include "./GameManagers/Menu.h"
#include <SFML/Graphics.hpp>

class Game : public I_Serialize
{
public:
    enum class State : uint8_t
    {
        None,
        Menu,
        NetWait,
        Prepare,
        GameProcess
    };

    struct GameData
    {
        std::string profileName;
        int levelUnlock = 0;
    };

private:
    sf::RenderWindow win;
    O_Manager& omger;
    R_Manager& rmger;
    Config& config;
    bool isRun;
    State currentState;
    Menu& menu;
    GameProcess gameProcess;
    GameData gameData;

    Game() :
        omger(O_Manager::get()),
        rmger(R_Manager::get()),
        win(sf::VideoMode(1000, 1000), "PVZ", sf::Style::Fullscreen),
        config(Config::getInstance()),
        menu(Menu::get()),
        isRun(true),
        currentState(State::Prepare)
    {
        try {
            // Загрузка конфигурации
            config.load("./Res/Config/Config.json");

            // Загрузка ресурсов
             rmger.pushFromFile(config["FileSystem"]["Resource"]);

            // Инициализация меню
            menu.start();
            setState(State::Menu);

            
           
        }
        catch (const std::exception& e) {
            std::cerr << "Game initialization error: " << e.what() << std::endl;
            isRun = false;
        }
    }

public:
    ~Game() = default;

    static Game& get() {
        static Game instance;
        return instance;
    }

    void run();

    bool isRunning() { return isRun; }
    void close() 
    { 
        isRun = false;
        saveGameData();
    }

    State getState() const { return currentState; }
    void setState(State state) { currentState = state; }

    void closeMenu() {
        menu.close();
    }

    // Сохранение данных игры в конфиг перед выходом
    void saveGameData() {
        config["GameData"]["profileName"] = gameData.profileName;
        config["GameData"]["levelUnlock"] = gameData.levelUnlock;
        config.save("./Res/Config/Config.json");
    }

    // Методы сериализации
    std::vector<char> serialize();

    std::pair<Types, std::pair<void*, int>> deserialize(std::vector<char> data, size_t& readPoint);
};