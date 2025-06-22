#pragma once
#include "Zombie.h"

class Child : public Zombie {
public:
    std::shared_ptr<Object> cool;
    bool rodi = true;
    Child(uint16_t line, std::shared_ptr<Object> creator)
        : Zombie(
            Config::getInstance()["ZombieParams"]["Zombies"]["Lilpampysya"]["HP"].get<int16_t>(),
            Config::getInstance()["ZombieParams"]["Zombies"]["Lilpampysya"]["Speed"].get<uint16_t>(),
            Config::getInstance()["ZombieParams"]["Zombies"]["Lilpampysya"]["Damage"].get<uint16_t>(),
            line,
            "child.png"
        ) {
        spr.setScale(0.1f, 0.1f);
        cool = creator;
    }

    void throwMyself()
    {
        if (rodi)
        {
            setPos(cool.get()->getPos());
            this->pos.x -= 250;
            this->rodi = false;
        }
    }

    void update() override
    {
        throwMyself();
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