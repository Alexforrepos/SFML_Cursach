#pragma once
#include "Projectile.h"

class FreezeProjectile :
    public Projectile
{

    void update() { Projectile::update(); };
    void sendMsg(const std::shared_ptr<Engine::MSG>& msg) override;
};

