#pragma once
#include <memory>
#include "Utils/Timer.h"     
class Zombie;

class Effect {
protected:
    Timer cooldown;
public:

    Effect(int period)
        : cooldown(period)
    {
        cooldown.restart();
    }

    virtual ~Effect() = default;

    virtual void influence(Zombie& target) = 0;

    bool tick(Zombie& target)
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
