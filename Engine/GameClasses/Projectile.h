#pragma once
#include "Engine/O_Manager.h"
static constexpr float MAX_X = 2000.f;
class Projectile
	:public Object

{

protected:
	uint16_t
		velocity,
		line,
		damage;
	sf::Sprite spr;
	bool isUpg = false;

	friend class FireLog;
public:

	Projectile() = default;

	Projectile(uint16_t velocity, uint16_t line, uint16_t damage, sf::Texture& texture, sf::Vector2f pos)
		:Object(int(Types::BaseProjectileType)), velocity(velocity), line(line), damage(damage), spr(texture)
	{
		setPos(pos);
		spr.setScale(0.1f, 0.1f);
	}
	void update() override {
		if (spr.getPosition().x > MAX_X) {
			MSG_Manager::get().addMSG(
				std::make_shared<Engine::MSG_TYPE_KILL>(this, this)
			);
			return;
		}
		MSG_Manager::get().addMSG(make_shared<Engine::MSG_TYPE_MOVE>(sf::Vector2f(static_cast<float>(velocity), 0.f), std::static_pointer_cast<Object>(this->shared_from_this())));
		spr.move(static_cast<float>(velocity), 0.f);
	}

	// 2) ������
	void draw(sf::RenderWindow& win) override {
		win.draw(spr);
	}

	// 3) ����������������
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

