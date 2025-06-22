#pragma once
#include "Zombie.h"
#include "Karapuz.h"

class Garg : public Zombie {
public:
    bool hasChild = true;
    Garg(uint16_t line)
        : Zombie(
            Config::getInstance()["ZombieParams"]["Zombies"]["Garantiryu"]["HP"].get<int16_t>(),
            Config::getInstance()["ZombieParams"]["Zombies"]["Garantiryu"]["Speed"].get<uint16_t>(),
            Config::getInstance()["ZombieParams"]["Zombies"]["Garantiryu"]["Damage"].get<uint16_t>(),
            line,
            "firestarter.png"
        ) {
        spr.setScale(0.1f, 0.1f);
    }

    void throwChild()
    {
        if (this->HP <= 250 && hasChild)
        {
            MSG_Manager::get().addMSG(
                std::make_shared<Engine::MSG_TYPE_CREATE>(
                    std::make_shared<Child>(getLine(), shared_from_this()),
                    nullptr
                )
            );
            hasChild = false;
        }
    }

    void update() override
    {
        throwChild();
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