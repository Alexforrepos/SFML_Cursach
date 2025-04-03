#pragma once
#include <vector>
#include "./../Utils/Timer.h"
#include "./../GameClasses/Button.h"	

class Menu
{
public:
    enum class State
    {
        Base = 1,
        Multiplayer,
        Settings
    };
private:
    class Basic_Menu
    {
        bool isRun;
        friend Menu;

        void start()
        {

        }
    };

    State state;
    bool isrun;

    Menu()
        : state(State::Base), isrun(false)
    {
    }

public:
    static void ChangeMode(const State& newState);

    static Menu& get()
    {
        static Menu inst;
        return inst;
    }

    void start();
    void run();
    void close();

    bool getIsRun() { return isrun; }
    State getCurrentState() { return state; }
};