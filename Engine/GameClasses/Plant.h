#pragma once
#include "Engine/Object.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "Engine/R_Manager.h"
#include "Utils/Timer.h"
#include "Utils/Config.h"
#include "Zombie.h"
class Plant : public Object
{
	friend class Surface;

protected:
	sf::Sprite sprite;
	std::string plantType;
	std::string textureId;
	uint8_t line, col;
	int16_t HP;
	bool isTakingDamage = true;

public:
	Plant() = default;


	Plant(const std::string& plantType,
		const std::string& textureId,
		uint8_t line,
		uint8_t col,
		int16_t HP)
		: Object(int(Types::BasePlantType))
		, plantType(plantType)
		, textureId(textureId)
		, line(line)
		, col(col)
		, HP(HP)
	{

		sprite.setTexture(R_Manager::get().access<sf::Texture>(textureId));
	}

	virtual ~Plant() = default;


	void draw(sf::RenderWindow& win) override {
		win.draw(sprite);
	}

	sf::Vector2f getPos() override
	{
		return sprite.getPosition();
	}

	void changePos(const sf::Vector2f& other) override {
		setPos(getPos() + other);
	}

	void setPos(sf::Vector2f other) override {
		sprite.setPosition(other);
	}

	void dealDamageToMyself(uint16_t damag1)
	{
		HP -= damag1;
	}

	int16_t getHp()
	{
		return HP;
	}

	std::string getType() 
	{ 
		return plantType; 
	}

	void sendMsg(const std::shared_ptr<Engine::MSG>& msg)
	{
		switch (msg->getIndex())
		{
		case Engine::MSG_TYPE::MSG_TYPE_MOVE:
		{
			auto msgmove = dynamic_cast<Engine::MSG_TYPE_MOVE*>(msg.get());

			if (!msgmove)
				return;

			
		}
		
		break;
		default:
			break;
		}
	}
};
