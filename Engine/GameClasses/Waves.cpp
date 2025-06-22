#include "Waves.h"
#include <cstdlib>

void WaveManager::populateWave(uint16_t wave) {
    waveZombies.clear();

    if (wave <= 2) {
        for (int i = 0; i < 4; ++i)
            waveZombies.push_back(std::make_shared<Zombie>(rand() % 5));
        for (int i = 0; i < 3; ++i)
            waveZombies.push_back(std::make_shared<ZombieBucket>(rand() % 5));
    }
    else if (wave <= 4) {
        for (int i = 0; i < 3; ++i)
            waveZombies.push_back(std::make_shared<ZombieBucket>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<Newsguy>(rand() % 5));
        for (int i = 0; i < 2; ++i)
            waveZombies.push_back(std::make_shared<Runner>(rand() % 5));
    }
    else if (wave <= 6) {
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
        waveZombies.clear();
    }
}

void WaveManager::update() {
    if (currentWave >= 25) return; 

    if (!isWaveActive && waveTimer()) {
        currentWave++;
        populateWave(currentWave);
        isWaveActive = true;
        spawnIndex = 0;
        spawnTimer.restart();
        waveTimer.restart();
    }

    if (isWaveActive && spawnTimer() && spawnIndex < waveZombies.size()) {
        MSG_Manager::get().addMSG(
            std::make_shared<Engine::MSG_TYPE_CREATE>(waveZombies[spawnIndex], nullptr)
        );
        spawnIndex++;
        spawnTimer.restart();
    }

    if (isWaveActive && spawnIndex >= waveZombies.size()) {
        isWaveActive = false;
    }
}