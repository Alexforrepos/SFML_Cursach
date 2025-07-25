#pragma once
#include "Zombie.h"

class HeavyRunner : public Zombie {
public:
    HeavyRunner(uint16_t line)
        : Zombie(
            Config::getInstance()["ZombieParams"]["Zombies"]["BasketballNogoy"]["HP"].get<int16_t>(),
            Config::getInstance()["ZombieParams"]["Zombies"]["BasketballNogoy"]["Speed"].get<uint16_t>(),
            Config::getInstance()["ZombieParams"]["Zombies"]["BasketballNogoy"]["Damage"].get<uint16_t>(),
            line,
            "FootBall.png"
        ) {
        spr.setScale(0.1f, 0.1f);
    }

    void update() override {
        loos();
        if (isAttack && attackTarget) {
            if (attackTimer()) {
                MSG_Manager::get().addMSG(
                    std::make_shared<Engine::MSG_TYPE_DAMAGE>(
                        damage,
                        attackTarget,
                        shared_from_this()
                    )
                );
                attackTimer.restart();
            }
        }
        else {
            if (moveTime()) {
                pos.x -= velocity;
                MSG_Manager::get().addMSG(
                    std::make_shared<Engine::MSG_TYPE_MOVE>(
                        sf::Vector2f{ -static_cast<float>(velocity), 0 },
                        shared_from_this()
                    )
                );
                spr.setPosition(pos);
                moveTime.restart();
            }
        }
        for (auto effect = effects.begin(); effect != effects.end(); ) {
            if ((*effect)->tick(*this)) {
                ++effect;
            }
            else {
                effect = effects.erase(effect);
            }
        }
    }
};