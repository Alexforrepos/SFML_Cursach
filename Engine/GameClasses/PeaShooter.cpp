#include "PeaShooter.h"
#include "Projectile.h"

PeaShooter::PeaShooter(const std::string& plantType, uint8_t line, uint8_t col)
	: Plant(
		plantType,
		"PeaShooter.png",  // textureId
		line,
		col,
		Config::getInstance()["PlantParams"]["Plants"]["PeaShooter"]["HP"]
	)
	, shootTimer(300)
{
	sprite.setScale(2.f, 2.f);
	sprite.setColor(sf::Color(255, 255, 255, 200));
	shootTimer.restart();
}

void PeaShooter::update()
{
	if (shootTimer()) {
		// 1. ������ �� ������� ��������� ����
		auto& cfg = Config::getInstance();
		unsigned damage = cfg["PlantParams"]["Plants"]["PeaShooter"]["Damage"].get<unsigned>();
		unsigned velocity = 5; // ���� ���� �� �������, ���� �����

		// 2. ������ shared_ptr �� Projectile
		//    �����������: Projectile(uint16_t velocity, uint16_t line, uint16_t damage, sf::Texture& texture)
		auto& tex = R_Manager::get().access<sf::Texture>("pea.jpg");
		auto proj = std::make_shared<Projectile>(
			static_cast<uint16_t>(velocity),
			line,                     // ����� ���������� �������� �����, ���� ������� � � PeaShooter
			static_cast<uint16_t>(damage),
			tex
		);

		// 3. ������������� ��������� ������� ������� � ����� PeaShooter
		proj->setPos(this->getPos());

		// 4. ������ ��������� � �������� ������ �������
		O_Manager::get().addObject(proj);

		shootTimer.restart();
	}
	else
		;
}

void PeaShooter::sendMsg(Engine::MSG* msg)
{

}




CEREAL_REGISTER_TYPE(PeaShooter);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Plant, PeaShooter);
