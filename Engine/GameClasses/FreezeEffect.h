#pragma once
#include "Effect.h"
#include <cstdint>

class Zombie;   // forward

class FreezeEffect : public Effect {
private:
    bool applied = false;
    float origSpeed = 0.f;

public:
    explicit FreezeEffect(uint32_t effectId);
    void refresh() {
        cooldown.restart();
        applied = true;
    }
    // переопределяем tick
    bool tick(Zombie& target) override;
    void influence(Zombie& target) override;  // всё равно пустая
};
