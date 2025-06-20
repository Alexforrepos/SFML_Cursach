#include "Waves.h"
#include <cstdlib>

void WaveManager::populateWave(uint16_t wave) {
    waveZombies.clear();

    if (wave <= 2) {
        // Waves 1-2: 4 Zombie, 3 ZombieBucket
        for (int i = 0; i < 4; ++i)
            waveZombies.push_back(std::make_shared<Zombie>(rand() % 5));
        for (int i = 0; i < 3; ++i)
            waveZombies.push_back(std::make_shared<ZombieBucket>(rand() % 5));
    }
    else if (wave <= 4) {
        // Waves 3-4: 3 ZombieBucket, 2 Newspaper, 2 Runner
        for (int i = 0; i < 3; ++i)
            waveZombies.push_back(std::make_shared<ZombieBucket>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<Newsguy>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<Runner>(rand() % 5));
    }
    else if (wave <= 6) {
        // Waves 5-6: 3 Runner, 1 Newspaper, 2 FootBall, 2 ZombieBucket, 2 Zombie
        for (int i = 0; i < 3; ++i)
            waveZombies.push_back(std::make_shared<Runner>(rand() % 5));
        waveZombies.push_back(std::make_shared<Newsguy>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<HeavyRunner>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<ZombieBucket>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<Zombie>(rand() % 5));
    }
    else if (wave <= 8) {
        // Waves 7-8: 4 Zombie, 3 FootBall, 3 Runner, 2 ZombieBucket
        for (int i = 0; i < 4; ++i)
            waveZombies.push_back(std::make_shared<Zombie>(rand() % 5));
        for (int i = 0; i < 3; ++i)
            waveZombies.push_back(std::make_shared<HeavyRunner>(rand() % 5));
        for (int i = 0; i < 3; ++i)
            waveZombies.push_back(std::make_shared<Runner>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<ZombieBucket>(rand() % 5));
    }
    else if (wave <= 10) {
        // Waves 9-10: 1 Zimin, 2 FootBall, 5 Zombie, 2 ZombieBucket, 2 Runner
        waveZombies.push_back(std::make_shared<Garg>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<HeavyRunner>(rand() % 5));
        for (int i = 0; i < 5; ++i)
            waveZombies.push_back(std::make_shared<Zombie>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<ZombieBucket>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<Runner>(rand() % 5));
    }
    else if (wave == 11) {
        // Wave 11: No zombies, trigger win condition
        waveZombies.clear();
    }
}

void WaveManager::update() {
    if (currentWave >= 25) return; // All waves complete

    // Check if it's time to start a new wave
    if (!isWaveActive && waveTimer()) {
        currentWave++;
        populateWave(currentWave);
        isWaveActive = true;
        spawnIndex = 0;
        spawnTimer.restart();
        waveTimer.restart();
    }

    // Spawn zombies with delay
    if (isWaveActive && spawnTimer() && spawnIndex < waveZombies.size()) {
        MSG_Manager::get().addMSG(
            std::make_shared<Engine::MSG_TYPE_CREATE>(waveZombies[spawnIndex], nullptr)
        );
        spawnIndex++;
        spawnTimer.restart();
    }

    // End wave when all zombies are spawned
    if (isWaveActive && spawnIndex >= waveZombies.size()) {
        isWaveActive = false;
    }
}