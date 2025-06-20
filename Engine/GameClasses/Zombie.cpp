#include "Zombie.h"
#include "Projectile.h"
#include "Plant.h"
#include "FreezeProjectile.h"
void Zombie::sendMsg(const std::shared_ptr<Engine::MSG>& msg) {
	switch (msg->getIndex()) {
	case Engine::MSG_TYPE::MSG_TYPE_MOVE: {
		auto moveMsg = std::static_pointer_cast<Engine::MSG_TYPE_MOVE>(msg);
		if (moveMsg->target.get() == this) {
			
			sf::Vector2f newPos = pos + moveMsg->dir;
			setPos(newPos);
		}
		else if (moveMsg->target->type() == int(Types::BaseProjectileType)) {
			
			auto fprj = dynamic_cast<FreezeProjectile*>(moveMsg->target.get());
			auto prj = dynamic_cast<Projectile*>      (moveMsg->target.get());

			if (fprj && !fprj->hasHit && fprj->getLine() == line && spr.getGlobalBounds().contains(fprj->getPos())) {
				fprj->hasHit = true;
				HP -= fprj->getDamage();

			
				auto freezeEff = std::make_shared<FreezeEffect>( 1);
				addEffect(freezeEff);
				std::cout << "Holodno" << std::endl;

				
				MSG_Manager::get().addMSG(
					std::make_shared<Engine::MSG_TYPE_KILL>(moveMsg->target.get(), this)
				);
				if (HP <= 0) {
					MSG_Manager::get().addMSG(
						std::make_shared<Engine::MSG_TYPE_KILL>(this, moveMsg->target.get())
					);
				}
			}
			
			else if (prj && !prj->hasHit && prj->getLine() == line && spr.getGlobalBounds().contains(prj->getPos())) {
				prj->hasHit = true;
				this->HP -= prj->getDamage();
				auto freeze = std::make_shared<FreezeEffect>(42);
				addEffect(freeze);
				std::cout << "  GOL" << std::endl;
				MSG_Manager::get().addMSG(
					std::make_shared<Engine::MSG_TYPE_KILL>(moveMsg->target.get(), this)
				);
				if (HP <= 0) {
					MSG_Manager::get().addMSG(
						std::make_shared<Engine::MSG_TYPE_KILL>(this, moveMsg->target.get())
					);
				}
			}
		}
		break;
	}
	case Engine::MSG_TYPE::MSG_TYPE_DAMAGE:
	{
		auto damageMsg = std::static_pointer_cast<Engine::MSG_TYPE_DAMAGE>(msg);
		auto plnt = dynamic_cast<Plant*>(damageMsg.get()->target.get());
		if (plnt == nullptr)
		{
			return;
		}
		if (this->isAttack)
		{
			std::cout << "nu3du/li oTnpaB/leHbl" << std::endl;
			plnt->dealDamageToMyself(this->damage);
			if (plnt->getHp() <= 0)
			{
				MSG_Manager::get().addMSG(
					std::make_shared<Engine::MSG_TYPE_KILL>(plnt, this)
				);
				this->attackTarget = nullptr; // Clear target when dead
				this->isAttack = false;
			}
		}
		break;
	}
	case Engine::MSG_TYPE::MSG_TYPE_KILL:
	{
		auto killMsg = std::static_pointer_cast<Engine::MSG_TYPE_KILL>(msg);

		if (killMsg->victim == this)
		{
			HP = 0;
			attackTarget = nullptr;
			isAttack = false;
		}
		else if (attackTarget && killMsg->victim == attackTarget.get())
		{
			attackTarget = nullptr;
			isAttack = false;
		}
	}
	break;

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
