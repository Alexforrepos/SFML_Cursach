#include "Repeater.h"

Repeater::Repeater(uint8_t line, uint8_t col)
    : PeaShooter(line, col)
    , secondShotTimer(100) 
    , pendingSecondShot(false)
{
    plantType = "Repeater";
    textureId = "Repeater.png";
    sprite.setTexture(R_Manager::get().access<sf::Texture>(textureId));
    sprite.setScale(0.15f, 0.15f);
    sprite.setColor(sf::Color(255, 255, 255, 200));
    shootTimer = Timer(1000);
    shootTimer.restart();
}

void Repeater::update() {
    if (!pendingSecondShot) {
        if (shootTimer()) {
            auto& cfg = Config::getInstance();
            unsigned damage = cfg["PlantParams"]["Plants"]["PeaShooter"]["Damage"].get<unsigned>();
            unsigned velocity = 2;
            auto& tex = R_Manager::get().access<sf::Texture>("pea.png");
            auto pos = getPos();
            MSG_Manager::get().addMSG(
                std::make_shared<Engine::MSG_TYPE_CREATE>(
                    std::make_shared<Projectile>(velocity, line, damage, tex, pos),
                    (Object*)this
                )
            );
            pendingSecondShot = true;
            secondShotTimer.restart();
            shootTimer.restart();
        }
    }
    else {
        if (secondShotTimer()) {
            auto& cfg = Config::getInstance();
            unsigned damage = cfg["PlantParams"]["Plants"]["PeaShooter"]["Damage"].get<unsigned>();
            unsigned velocity = 2;
            auto& tex = R_Manager::get().access<sf::Texture>("pea.png");
            auto pos = getPos();
            MSG_Manager::get().addMSG(
                std::make_shared<Engine::MSG_TYPE_CREATE>(
                    std::make_shared<Projectile>(velocity, line, damage, tex, pos),
                    (Object*)this
                )
            );
            pendingSecondShot = false;
        }
    }
}
