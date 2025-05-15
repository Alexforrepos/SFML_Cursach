#pragma once
#include "Plant.h"
#include "Projectile.h"


class FireLog :
	public Plant
{


public:

	FireLog(uint8_t line, uint8_t col)
		:Plant("FireLog", "Firelog.jpg", line, col, 5)
	{
		sprite.setScale(0.1f, 0.1f);
		sprite.setColor(sf::Color(255, 255, 255, 200));

	}

	void update() override
	{

	}

	void sendMsg(const std::shared_ptr<Engine::MSG>& msg)
	{
		switch (msg->getIndex())
		{
		case Engine::MSG_TYPE::MSG_TYPE_MOVE:
		{
			Engine::MSG_TYPE_MOVE* msgMove = dynamic_cast<Engine::MSG_TYPE_MOVE*>(msg.get());
			if (!msgMove || !msgMove->target) return;

			if (msgMove->target->type() == int(Types::BaseProjectileType))
			{
				auto projectile = dynamic_cast<Projectile*>(msgMove->target.get());
				if (!projectile || projectile->isUpg) return;

				sf::FloatRect firelogBounds = this->sprite.getGlobalBounds();
				sf::FloatRect projectileBounds = projectile->spr.getGlobalBounds();

				if (firelogBounds.intersects(projectileBounds))
				{
					projectile->damage *= 2;
					projectile->spr.setColor({ 100,255,255,200 });
					projectile->isUpg = true;
				}
			}
		}
		break;
		case Engine::MSG_TYPE::MSG_TYPE_DAMAGE:
		{
			Engine::MSG_TYPE_DAMAGE* msgDamage = dynamic_cast<Engine::MSG_TYPE_DAMAGE*>(msg.get());
			if (!msgDamage) return;

			if (msgDamage->target.get() == this) this->HP -= msgDamage->damage;
			if (this->HP <= 0) MSG_Manager::get().addMSG(std::make_shared<Engine::MSG_TYPE_KILL>(msgDamage->target.get(), msgDamage->damager.get()));
		}
		break;

		default:
			break;
		}

	}

};

