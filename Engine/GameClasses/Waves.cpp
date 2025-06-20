#include "Waves.h"
#include <cstdlib>

void WaveManager::populateWave(uint16_t wave) {
    waveZombies.clear();

    if (wave <= 5) {
        // Waves 1-5: 4 Zombie, 3 ZombieBucket
        for (int i = 0; i < 4; ++i)
            waveZombies.push_back(std::make_shared<Zombie>(rand() % 5));
        for (int i = 0; i < 3; ++i)
            waveZombies.push_back(std::make_shared<ZombieBucket>(rand() % 5));
    }
    else if (wave <= 10) {
        // Waves 6-10: 3 ZombieBucket, 2 Newspaper, 2 Runner
        for (int i = 0; i < 3; ++i)
            waveZombies.push_back(std::make_shared<ZombieBucket>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<Newsguy>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<Runner>(rand() % 5));
    }
    else if (wave <= 15) {
        // Waves 10-15: 3 Runner, 1 Newspaper, 2 HeavyRunner, 2 ZombieBucket, 2 Zombie
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
    else if (wave <= 20) {
        // Waves 15-20: 4 Zombie, 3 HeavyRunner, 3 Runner, 2 ZombieBucket
        for (int i = 0; i < 4; ++i)
            waveZombies.push_back(std::make_shared<Zombie>(rand() % 5));
        for (int i = 0; i < 3; ++i)
            waveZombies.push_back(std::make_shared<HeavyRunner>(rand() % 5));
        for (int i = 0; i < 3; ++i)
            waveZombies.push_back(std::make_shared<Runner>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<ZombieBucket>(rand() % 5));
    }
    else {
        // Waves 20-25: 1 Zimin, 2 HeavyRunner, 5 Zombie, 2 ZombieBucket
        waveZombies.push_back(std::make_shared<Garg>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<HeavyRunner>(rand() % 5));
        for (int i = 0; i < 5; ++i)
            waveZombies.push_back(std::make_shared<Zombie>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<ZombieBucket>(rand() % 5));
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