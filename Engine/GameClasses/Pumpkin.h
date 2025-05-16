#pragma once
#include "Plant.h"
#include "Engine/MSG_Manager.h"
class Pumpkin : public Plant
{
	friend class Surface;


	std::shared_ptr<Plant> original_plant; 

public:
	Pumpkin(uint8_t line, uint8_t col)
		: Plant(
			"Pumpkin",
			Config::getInstance()["PlantParams"]["Plants"]["Pumpkin"]["textureId"],
			line, col,
			Config::getInstance()["PlantParams"]["Plants"]["Pumpkin"]["HP"])
	{
		sprite.setScale(0.1f, 0.1f);
		sprite.setColor(sf::Color(255, 255, 255, 200)); 
	}

	void setPlant(std::shared_ptr<Plant> pl) {
		original_plant = pl; // Просто сохраняем shared_ptr
	}

	void update() override {
		if (original_plant) {
			original_plant->update();
		}
	}

	void sendMsg(const std::shared_ptr<Engine::MSG>& msg) override {
		switch (msg->getIndex())
		{
		case Engine::MSG_TYPE::MSG_TYPE_DAMAGE:
			if (auto damage_msg = dynamic_cast<Engine::MSG_TYPE_DAMAGE*>(msg.get()))
			{
				this->HP -= damage_msg->damage;
				if (this->HP <= 0) {
					// Убиваем тыкву
					MSG_Manager::get().addMSG(
						std::make_shared<Engine::MSG_TYPE_KILL>(this, damage_msg->damager.get())
					);
				}
			}
			break;
		default:
			break;
		}
	}

	virtual void draw(sf::RenderWindow& win)
	{
		if (original_plant) original_plant->draw(win);
		win.draw(sprite);
	}

	std::shared_ptr<Plant> getOriginalPlant() { return original_plant; }
};
