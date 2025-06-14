#include "Zombie.h"
#include "Projectile.h"

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
		if (moveMsg->target->type() == int(Types::BaseProjectileType)) {
			auto prj = dynamic_cast<Projectile*>(moveMsg->target.get());
			if (!prj) return;
			// Проверяем не только позиционное пересечение, но и совпадение линии
			if (prj->getLine() == this->getLine()
				&& spr.getGlobalBounds().contains(prj->getPos())) {
				// Попадание по зомби на этой же линии
				this->HP -= prj->getDamage();
				std::cout << " ___________________________________________ " << std::endl;
				// Уничтожаем снаряд
				MSG_Manager::get().addMSG(
					std::make_shared<Engine::MSG_TYPE_KILL>(prj, this)
				);
			}
		}
		break;
	}
	case Engine::MSG_TYPE::MSG_TYPE_DAMAGE:
	{
		auto damageMsg = std::static_pointer_cast<Engine::MSG_TYPE_DAMAGE>(msg);
		if (damageMsg->target.get() == this)
		{
			if (HP <= damageMsg->damage)
			{
				MSG_Manager::get().addMSG(
					std::make_shared<Engine::MSG_TYPE_KILL>(this, damageMsg->damager.get())
				);
				HP = 0;
				attackTarget = nullptr; // Clear target when dead
				isAttack = false;
			}
			else
			{
				HP -= damageMsg->damage;
			}
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
