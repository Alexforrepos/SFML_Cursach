#pragma once
#include "./../../Engine/O_Manager.h"
#include "./../GameClasses/Surface.h"
#include "./../Utils/Timer.h"
#include <SFML/Window/Event.hpp>

class GameProcess
{
    bool m_isActive;
    uint16_t m_sunQuantity;

public:
    GameProcess() : m_isActive(false), m_sunQuantity(0) {}

    bool isRunning() const { return m_isActive; }
    uint16_t getSun() const { return m_sunQuantity; }

    void start(int levelNumber);
    void run();
    void close();
    void handleEvent(const sf::Event& event);

    static GameProcess& get()
    {
        static GameProcess instance;
        return instance;
    }
};