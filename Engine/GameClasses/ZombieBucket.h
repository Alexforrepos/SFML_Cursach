#pragma once
#include "Zombie.h"

class ZombieBucket : public Zombie {
public:
    ZombieBucket(uint16_t line)
        : Zombie(
            Config::getInstance()["ZombieParams"]["Zombies"]["ZombieBucket"]["HP"].get<int16_t>(),
            Config::getInstance()["ZombieParams"]["Zombies"]["ZombieBucket"]["Speed"].get<uint16_t>(),
            Config::getInstance()["ZombieParams"]["Zombies"]["ZombieBucket"]["Damage"].get<uint16_t>(),
            line,
            "Bucket.png" 
        ) {
        spr.setScale(0.09f, 0.09f); 
    }

    void textureChangeAfterRape() {
        if (HP <= 100) {
            spr.setTexture(R_Manager::get().access<sf::Texture>("bullet.png"));
        }
    }

    void update() override {
        textureChangeAfterRape();
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