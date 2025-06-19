#pragma once
#include "Zombie.h"
#include "Zimin.h"

class Child : public Zombie {
public:
    bool rodi = true;
    Child(uint16_t line, std::shared_ptr<Object> creator)
        : Zombie(
            Config::getInstance()["ZombieParams"]["Zombies"]["Lilpampysya"]["HP"].get<int16_t>(),
            Config::getInstance()["ZombieParams"]["Zombies"]["Lilpampysya"]["Speed"].get<uint16_t>(),
            Config::getInstance()["ZombieParams"]["Zombies"]["Lilpampysya"]["Damage"].get<uint16_t>(),
            line,
            "pea.gif"
        ) {
        spr.setScale(0.5f, 0.5f);
        spr.setPosition(creator.get()->getPos());
    }

    void iWasBornByBigDudeWithBat()
    {
        if (rodi)
        {
            this->pos.x -= 250;
            this->rodi = false;
        }
    }

    void update() override
    {
        iWasBornByBigDudeWithBat();
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