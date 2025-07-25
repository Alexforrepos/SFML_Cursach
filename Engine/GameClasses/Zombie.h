#pragma once
#include "Engine/O_Manager.h"
#include "GameClasses/Effect.h"
#include "Utils/Config.h"
#include "Utils/Timer.h"
#include <SFML/Graphics.hpp>
#include "Plant.h"
#include "FreezeEffect.h"
class Zombie : public Object
{
protected:
	friend class Effect;
	friend class Projectile;
	sf::Vector2f pos;
	int16_t HP;
	uint16_t velocity; // = speed
	uint16_t damage;
	uint16_t line;
	sf::Sprite spr;
	sf::Sprite tgfy;
	bool isAttack;
	std::shared_ptr<Object> attackTarget; // Stores attack target
	std::vector<EffectPtr> effects;
	Timer attackTimer, moveTime;

public:
	Zombie() = default;

	Zombie(const int16_t& HP, const uint16_t& velocity, const uint16_t& damage, const uint16_t& line, std::string textureId)
		: Object(int(Types::BaseZombieType)), HP(HP), velocity(velocity), damage(damage), line(line), isAttack(false), attackTarget(nullptr),attackTimer(Config::getInstance()
			["ZombieParams"]["Zombies"]["Zombie"]["CD"]
			.get<int>() * 1000)  
		, moveTime(1000 / velocity)  
	{
		spr.setTexture(R_Manager::get().access<sf::Texture>(textureId));
	}
	~Zombie()
	{
		std::cout << "zomb ";
	}

	Zombie(const uint16_t& line)
		: Zombie(
			Config::getInstance()["ZombieParams"]["Zombies"]["Zombie"]["HP"],
			Config::getInstance()["ZombieParams"]["Zombies"]["Zombie"]["Speed"],
			Config::getInstance()["ZombieParams"]["Zombies"]["Zombie"]["Damage"],
			line,
			"bullet.png")
	{
		spr.setScale(0.09f, 0.09f);
	}

	unsigned getLine() { return line; };

	void draw(sf::RenderWindow& win) override
	{
		win.draw(spr);
		win.draw(tgfy);
	}

	sf::Vector2f getPos() override
	{
		return pos;
	}

	void setPos(sf::Vector2f other) override
	{
		this->pos = other;
		spr.setPosition(other);
	}

	void changePos(const sf::Vector2f& pos) override
	{
		if (moveTime())
		{
			//logMessage("moved");
			this->pos.x -= velocity;
			MSG_Manager::get().addMSG(std::make_shared<Engine::MSG_TYPE_MOVE>(sf::Vector2f{ float(0 - velocity),0 }, shared_from_this()));
			spr.setPosition(this->pos);
			moveTime.restart();
		}
	}

	void setAttackTarget(std::shared_ptr<Object> target)
	{
		attackTarget = target;
		isAttack = (target != nullptr);
	}

	void loos()
	{
		if (pos.x <= 250)
		{
			tgfy.setTexture(R_Manager::get().access<sf::Texture>(
				"gamover.png"));
			tgfy.setPosition(400, 200);
		}
	}

	std::shared_ptr<Object> getTarget()
	{
		return attackTarget;
	}

	void update() override
	{	
		loos();
		if (isAttack && attackTarget)
		{
			if (attackTimer())
			{
				
				MSG_Manager::get().addMSG(
					std::make_shared<Engine::MSG_TYPE_DAMAGE>(
						damage,
						attackTarget,
						shared_from_this()
					)
				);
				std::cout << "ATTACK" << std::endl;
				attackTimer.restart();
			}
		}
		else
		{
			if (moveTime())
			{
				
				this->pos.x -= velocity;
				MSG_Manager::get().addMSG(
					std::make_shared<Engine::MSG_TYPE_MOVE>(
						sf::Vector2f{ -float(velocity), 0 },
						shared_from_this()
					)
				);
				spr.setPosition(pos);
				moveTime.restart();
			}
		}
		for (auto effect = effects.begin(); effect != effects.end(); )
		{
			if ((*effect)->tick(*this))
			{
				effect++;
			}
			else
			{
				effect = effects.erase(effect);
			}
		}
	}

	void sendMsg(const std::shared_ptr<Engine::MSG>& msg) override;

	void addEffect(const EffectPtr& eff)
	{
		effects.push_back(eff);
	}

	void removeEffect(const EffectPtr& eff = nullptr)
	{
		if (!eff)
		{
			effects.clear();
		}
		else
		{
			effects.erase(std::remove(effects.begin(), effects.end(), eff), effects.end());
		}
	}
	float getSpeed() const 
	{ 
		return static_cast<float>(velocity); 
	}
	
	void setSpeed(float s)
	{
		velocity = static_cast<uint16_t>(s); 
	}
};