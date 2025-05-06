#pragma once
#include "Engine/O_Manager.h"
static constexpr float MAX_X = 2000.f;
class Projectile
	:public Object
{
	uint16_t
		velocity,
		line,
		damage;
	sf::Sprite spr;
public:
	Projectile(uint16_t velocity, uint16_t line, uint16_t damage,sf::Texture& texture)
		:Object(int(Types::BaseProjectileType)), velocity(velocity), line(line), damage(damage), spr(texture)
	{
        spr.setScale(0.1f, 0.1f);
	}
    void update() override {
        if (spr.getPosition().x > MAX_X) {
            MSG_Manager::get().addMSG(
                std::make_shared<Engine::MSG_TYPE_KILL>(this, this)
            );
            return;
        }
        spr.move(static_cast<float>(velocity), 0.f);
    }

    // 2) Рисуем
    void draw(sf::RenderWindow& win) override {
        win.draw(spr);
    }

    // 3) Позиционирование
    sf::Vector2f getPos() override {
        return spr.getPosition();
    }
    void setPos(sf::Vector2f other) override {
        spr.setPosition(other);
    }
    void changePos(const sf::Vector2f& delta) override {
        spr.setPosition(spr.getPosition() + delta);
    }
};

