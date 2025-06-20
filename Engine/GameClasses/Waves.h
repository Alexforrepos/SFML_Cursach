#pragma once
#include "Engine/MSG_Manager.h"
#include "GameClasses/Zombie.h"
#include "GameClasses/ZombieBucket.h"
#include "GameClasses/Newspaper.h"
#include "GameClasses/Runner.h"
#include "GameClasses/FootBall.h"
#include "GameClasses/Zimin.h"
#include "Utils/Timer.h"
#include <vector>
#include <memory>

class WaveManager {
private:
    uint16_t currentWave = 0; // Current wave number (1 to 25)
    Timer waveTimer;          // Timer for wave activation (25 seconds)
    Timer spawnTimer;         // Timer for intra-wave spawn delays (1 second)
    bool isWaveActive = false; // Whether a wave is currently spawning
    std::vector<std::shared_ptr<Zombie>> waveZombies; // Zombies to spawn in current wave
    size_t spawnIndex = 0;    // Index of next zombie to spawn

    WaveManager()
        : waveTimer(25000),   // 25 seconds between waves
        spawnTimer(1000)    // 1 second between zombie spawns
    {
    }

    // Populate waveZombies with zombies for the given wave
    void populateWave(uint16_t wave);

public:
    static WaveManager& get() {
        static WaveManager instance;
        return instance;
    }

    // Start wave system
    void start() {
        currentWave = 0;
        isWaveActive = false;
        waveZombies.clear();
        spawnIndex = 0;
        waveTimer.restart();
    }

    // Update wave system, called from GameProcess::run
    void update();

    // Check if all waves are complete
    bool isComplete() const { return currentWave >= 25 && !isWaveActive; }
};