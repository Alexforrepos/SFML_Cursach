#include "Zombie.h"
#include "Projectile.h"
#include "Plant.h"

void Zombie::sendMsg(const std::shared_ptr<Engine::MSG>& msg) {
	switch (msg->getIndex()) {
	case Engine::MSG_TYPE::MSG_TYPE_MOVE: {
		auto moveMsg = std::static_pointer_cast<Engine::MSG_TYPE_MOVE>(msg);
		// Стандартное смещение самого зомби
		if (moveMsg->target.get() == this) {
			sf::Vector2f newPos = pos + moveMsg->dir;
			setPos(newPos);
		}
		// Обработка перемещения снаряда
		if (moveMsg->target->type() == int(Types::BaseProjectileType)) 
		{
			auto prj = dynamic_cast<Projectile*>(moveMsg->target.get());
			if (prj && !prj->hasHit && prj->getLine() == this->getLine() && spr.getGlobalBounds().contains(prj->getPos())) 
			{
				prj->hasHit = true;
				this->HP -= prj->getDamage();
				std::cout << "  GOL" << std::endl;
				MSG_Manager::get().addMSG(
					std::make_shared<Engine::MSG_TYPE_KILL>(prj, this)
				);
				if (this->HP <= 0)
				{
					MSG_Manager::get().addMSG(
						std::make_shared<Engine::MSG_TYPE_KILL>(this, prj));
				}
			}
		}
		break;
	}
	case Engine::MSG_TYPE::MSG_TYPE_DAMAGE:
	{
		Timer timeToEat = this->CD * 1000;
		auto damageMsg = std::static_pointer_cast<Engine::MSG_TYPE_DAMAGE>(msg);
		auto plnt = dynamic_cast<Plant*>(damageMsg->target.get());
		if (plnt && plnt->getLine() == this->getLine() && spr.getGlobalBounds().contains(plnt->getPos()))
		{
			std::cout << "BRAIIIINSSSSSS" << std::endl;
			uint16_t iWasLikeThis = this->velocity;
			this->velocity = 0;
			this->isAttack = true;
			while (this->isAttack)
			{
				if (timeToEat())
				{
					std::cout << "kykish" << std::endl;
					plnt->minusHP(this->damage);
				}
				if (plnt->getHP() <= 0)
				{
					std::cout << "kakish" << std::endl;
					MSG_Manager::get().addMSG(
						std::make_shared<Engine::MSG_TYPE_KILL>(plnt, this));
					this->isAttack = false;
					this->velocity = iWasLikeThis;
				}
			}
		/*	MSG_Manager::get().addMSG(
				std::make_shared<Engine::MSG_TYPE_KILL>(this, damageMsg->damager.get()));*/
		}
		break;
	}
	case Engine::MSG_TYPE::MSG_TYPE_KILL:
	{
		auto killMsg = std::static_pointer_cast<Engine::MSG_TYPE_KILL>(msg);
		if (killMsg->victim == this)
		{
			HP = 0; // Mark as dead
			attackTarget = nullptr; // Clear target
			isAttack = false;
		}
		break;
	}
	/*case Engine::MSG_TYPE::MSG_TYPE_ADD_EFFECT:
	{
	auto effectMsg = std::static_pointer_cast<Engine::MSG_TYPE_ADD_EFFECT>(msg);
	if (effectMsg->target.get() == this)
	{
	addEffect(effectMsg->effect);
	}
	break;
	}*/
	case Engine::MSG_TYPE::MSG_TYPE_REMOVE_EFFECT:
	{
		auto removeEffectMsg = std::static_pointer_cast<Engine::MSG_TYPE_REMOVE_EFFECT>(msg);
		if (removeEffectMsg->targetId == this->getId())
		{
			for (auto it = effects.begin(); it != effects.end(); )
			{
				if ((*it)->getId() == removeEffectMsg->effectId)
				{
					it = effects.erase(it);
				}
				else
				{
					++it;
				}
			}
		}
		break;
	}
	default:
		break; // Ignore unhandled message types
	}
}
