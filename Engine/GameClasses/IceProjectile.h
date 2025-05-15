#pragma once
#include "Projectile.h"
#include "Engine/O_Manager.h"
#include "GameClasses/Zombie.h"
#include "Engine/MSG_Manager.h"
#include "Engine/MSG.h"
class IceProjectile : public Projectile {
public:
    IceProjectile(uint16_t velocity, uint16_t line, uint16_t damage,
        sf::Texture& texture, sf::Vector2f startPos);

    void update() override;
};