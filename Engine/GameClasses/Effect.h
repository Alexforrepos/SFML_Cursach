#pragma once
#include <memory>
#include <cstdint>
#include "Utils/Timer.h"

class Zombie;

class Effect {
protected:
    Timer cooldown;
public:
    friend class Zombie;

    uint32_t id; 

public:
    Effect(int period, uint32_t effectId)
        : cooldown(period), id(effectId)
    {
        cooldown.restart();
    }

    virtual ~Effect() = default;

    uint32_t getId() const { return id; }

    virtual void influence(Zombie& target) = 0;

   virtual bool tick(Zombie& target)
    {
        if (!cooldown())
        {
            influence(target);
            return true;
        }
        return false;
    }
};

using EffectPtr = std::shared_ptr<Effect>;