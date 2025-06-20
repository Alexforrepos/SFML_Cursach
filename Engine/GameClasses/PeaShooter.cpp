#include "PeaShooter.h"
#include "Projectile.h"

PeaShooter::PeaShooter( uint8_t line, uint8_t col)
	: Plant(
		"PeaShooter",
		"PeaShooter.png",  // textureId
		line,
		col,
		Config::getInstance()["PlantParams"]["Plants"]["PeaShooter"]["HP"]
	)
	, shootTimer(1000)
{
	sprite.setScale(0.2,0.2);
	sprite.setColor(sf::Color(255, 255, 255, 200));
	shootTimer.restart();
}

void PeaShooter::update()
{
	if (shootTimer()) {
		// 1. Достаём из конфига параметры пули
		auto& cfg = Config::getInstance();
		unsigned damage = cfg["PlantParams"]["Plants"]["PeaShooter"]["Damage"].get<unsigned>();
		unsigned velocity = 3; // либо тоже из конфига, если нужно

		// 2. Создаём shared_ptr на Projectile
		//    Конструктор: Projectile(uint16_t velocity, uint16_t line, uint16_t damage, sf::Texture& texture)
		auto& tex = R_Manager::get().access<sf::Texture>("pea.png");


		// 3. Устанавливаем стартовую позицию снаряда в точку PeaShooter

		auto pos = getPos();
		// 4. Кидаем сообщение о создании нового объекта
		MSG_Manager::get().addMSG(std::make_shared<Engine::MSG_TYPE_CREATE>(std::make_shared<Projectile>(
			static_cast<uint16_t>(velocity),
			line,                     // можно передавать реальную линию, если храните её в PeaShooter
			static_cast<uint16_t>(damage),
			tex,
			pos
		),
			(Object*)this
		));

		shootTimer.restart();
	}
	else
		;
}

void PeaShooter::sendMsg(const std::shared_ptr<Engine::MSG>& msg)
{

}



//
//CEREAL_REGISTER_TYPE(PeaShooter);
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Plant, PeaShooter);
