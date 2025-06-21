#include "FreezeEffect.h"
#include "GameClasses/Zombie.h"
#include "Engine/MSG_Manager.h"
#include <algorithm>

static constexpr uint32_t DURATION_MS = 3000;

FreezeEffect::FreezeEffect(uint32_t effectId)
    : Effect(DURATION_MS, effectId)
{
}

bool FreezeEffect::tick(Zombie& target) {
    // при первом тике сохран€ем оригинальную скорость и снижаем
    if (!applied) {
        origSpeed = target.getSpeed();
        target.setSpeed(std::max(0.f, origSpeed - 0.5f));
        applied = true;
    }

    // если врем€ ещЄ не вышло Ч держим эффект
    if (!cooldown()) {
        return true;
    }

    // врем€ вышло Ч возвращаем скорость и шлЄм MSG_REMOVE
    target.setSpeed(origSpeed);
    MSG_Manager::get().addMSG(
        std::make_shared<Engine::MSG_TYPE_REMOVE_EFFECT>(
            target.getId(), getId()
        )
    );
    return false;  // говорим, что эффект завершаетс€
}

void FreezeEffect::influence(Zombie& /*target*/) {
    // не используетс€
}
