#include "Projectile.h"
#include "GameClasses/Zombie.h"
#include "FreezeEffect.h"
#include "Engine/MSG_Manager.h"

class FreezeProjectile : public Projectile {
public:
    FreezeProjectile(uint16_t velocity, uint16_t line, uint16_t damage, sf::Texture& texture, sf::Vector2f pos)
        : Projectile(velocity, line, damage, texture, pos) {
        spr.setColor(sf::Color(0, 0, 255, 200));  // Синий цвет
    }

    void update() override {
        Projectile::update();
    }

   /* void onCollision(Zombie* zombie) override {
        auto effect = std::make_shared<FreezeEffect>();
        MSG_Manager::get().addMSG(std::make_shared<Engine::MSG_TYPE_ADD_EFFECT>(effect, zombie->shared_from_this()));
        MSG_Manager::get().addMSG(std::make_shared<Engine::MSG_TYPE_KILL>(this, this));
    }*/
};