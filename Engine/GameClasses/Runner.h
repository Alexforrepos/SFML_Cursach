#pragma once
#include "Zombie.h"

class Runner : public Zombie {
public:
    bool canJump = true;
    Runner(uint16_t line)
        : Zombie(
            Config::getInstance()["ZombieParams"]["Zombies"]["Prigyn"]["HP"].get<int16_t>(),
            Config::getInstance()["ZombieParams"]["Zombies"]["Prigyn"]["Speed"].get<uint16_t>(),
            Config::getInstance()["ZombieParams"]["Zombies"]["Prigyn"]["Damage"].get<uint16_t>(),
            line,
            "runner.png"
        ) {
        spr.setScale(0.25f, 0.25f);
    }

    void jumpRightOnThePlantsDicks()
    {
        if (canJump && isAttack && attackTarget)
        {
            this->pos.x -= 180;
            this->canJump = false;
            this->isAttack = false;
            this->attackTarget = nullptr;
            this->velocity = 4;
            this->moveTime = 1000 / 4;
        }
    }

    void update() override 
    {
        if (isAttack && attackTarget) {
            jumpRightOnThePlantsDicks();
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