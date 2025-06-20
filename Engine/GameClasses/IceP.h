#include "PeaShooter.h"
#include "FreezeProjectile.h"
#include "Utils/Timer.h"
#include "Engine/R_Manager.h"
#include "Engine/MSG_Manager.h"
#include "Utils/Config.h"

class IceP : public PeaShooter {
public:
    // Конструктор по умолчанию
    IceP() : PeaShooter(0, 0) {
       sprite.setTexture(R_Manager::get().access<sf::Texture>("IceP.png"));
    }

    // Конструктор с параметрами
    IceP(uint8_t line, uint8_t col)
        : PeaShooter(line, col) {
       sprite.setTexture(R_Manager::get().access<sf::Texture>("IceP.png"));
    }

    void update() override {
        if (shootTimer()) {
            auto& cfg = Config::getInstance();
            unsigned damage = cfg["PlantParams"]["Plants"]["IceP"]["Damage"].get<unsigned>();
            unsigned velocity = 2;

            auto& tex = R_Manager::get().access<sf::Texture>("Seed.png");
            auto pos = getPos();
            auto projectile = std::make_shared<FreezeProjectile>(
                static_cast<uint16_t>(velocity),
                line,
                static_cast<uint16_t>(damage),
                tex,
                pos
            );

            MSG_Manager::get().addMSG(std::make_shared<Engine::MSG_TYPE_CREATE>(projectile, this));
            shootTimer.restart();
        }
    }
};