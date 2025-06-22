#pragma once
#include "Engine/O_Manager.h"
#include "GameClasses/Surface.h"
#include "GameClasses/Waves.h"
#include "Utils/Timer.h"
#include <SFML/Window/Event.hpp>

class GameProcess
{
    bool m_isActive;
    uint16_t m_sunQuantity;
    Timer m_winTimer{ 260000 }; // 2 минуты
    bool m_hasWon = false;
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