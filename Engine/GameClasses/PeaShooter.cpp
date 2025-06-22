#include "PeaShooter.h"
#include "Projectile.h"

PeaShooter::PeaShooter( uint8_t line, uint8_t col)
	: Plant(
		"PeaShooter",
		"PeaShooter.png", 
		line,
		col,
		Config::getInstance()["PlantParams"]["Plants"]["PeaShooter"]["HP"]
	)
	, shootTimer(1000)
{
	sprite.setScale(0.1,0.1);
	sprite.setColor(sf::Color(255, 255, 255, 200));
	shootTimer.restart();
}

void PeaShooter::update()
{
	if (shootTimer()) {

		auto& cfg = Config::getInstance();
		unsigned damage = cfg["PlantParams"]["Plants"]["PeaShooter"]["Damage"].get<unsigned>();
		unsigned velocity = 2; 

		
		auto& tex = R_Manager::get().access<sf::Texture>("pea.png");




		auto pos = getPos();

		MSG_Manager::get().addMSG(std::make_shared<Engine::MSG_TYPE_CREATE>(std::make_shared<Projectile>(
			static_cast<uint16_t>(velocity),
			line,                    
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
