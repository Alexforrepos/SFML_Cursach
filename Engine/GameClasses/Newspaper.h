#pragma once
#include "Zombie.h"

class Newsguy : public Zombie {
public:
    Newsguy(uint16_t line)
        : Zombie(
            Config::getInstance()["ZombieParams"]["Zombies"]["Newspaper"]["HP"].get<int16_t>(),
            Config::getInstance()["ZombieParams"]["Zombies"]["Newspaper"]["Speed"].get<uint16_t>(),
            Config::getInstance()["ZombieParams"]["Zombies"]["Newspaper"]["Damage"].get<uint16_t>(),
            line,
            "igotsomebadnews.jpg"
        ) {
        spr.setScale(0.5f, 0.5f);
    }

    void didIlostMyShield()
    {
        if (this->HP <= 0)
        {
            this->velocity = 7;
            this->moveTime = 1000 / velocity;
            spr.setTexture(R_Manager::get().access<sf::Texture>("rambo.png"));
            spr.setScale(0.8f, 0.8f);
        }
    }

    void update() override
    {
        didIlostMyShield();
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