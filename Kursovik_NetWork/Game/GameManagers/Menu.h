#pragma once
#include "iostream" 
#include <vector>
#include "./../../Engine/R_Manager.h"
#include "./../Utils/Timer.h"
#include "./../Interfaces/InterfaceIntputText.h"
#include "./../Interfaces/InterfaceWindow.h"
#include "./../Interfaces/Button_.h"

class Menu
{
public:

    friend class Game;

    enum class State
    {
        Base = 1,
        Multiplayer,
        Settings
    };

private:
    sf::RectangleShape m_background;
    std::unique_ptr<InterfaceWindow> m_currentWindow;
    State m_state;
    bool m_change;
    bool m_isRunning;

   

    void createBaseMenu();
    void createMultiplayerMenu();
    void createSettingsMenu();



public:

    Menu()
        : m_state(State::Base), m_isRunning(false), m_change(false),
        m_background({ 0,0 })
    {
    }

    friend void SETTINGS();
    friend void BACK_TO_MAIN();
    friend void MULT();

    static Menu& get()
    {
        static Menu* inst = new Menu();
        return *inst;
    }

    void start();
    void run();
    void close();

    bool isRunning() const { return m_isRunning; }
    State getCurrentState() const { return m_state; }
    void changeState(const State& newState);
};