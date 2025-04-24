#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Interfaces/Button_.h"
#include "../Interfaces/InterfaceIntputText.h"
#include "./../../Engine/R_Manager.h"
#include "./../Utils/Timer.h"
#include "./../Interfaces/InterfaceWindow.h"

class Menu
{
public:
    enum class State
    {
        Base = 1,
        Start,
        Multiplayer,
        Settings
    };

private:
    sf::RectangleShape m_background;
    std::unique_ptr<InterfaceWindow> m_currentWindow;
    State m_state;
    bool m_change;
    bool m_isRunning;
    sf::Music& m_music;

    void createBaseMenu();
    void createMultiplayerMenu();
    void createSettingsMenu();
    void createStartMenu();

public:
    Menu();
    ~Menu() = default;

    static Menu& get()
    {
        static Menu* instance = new Menu;
        return *instance;
    }

    void start();
    void run();
    void close();
    void handleEvent(const sf::Event& event) { m_currentWindow->handleEvent(event); };
    void changeState(const State& newState);

    bool isRunning() const { return m_isRunning; }
    State getCurrentState() const { return m_state; }
};