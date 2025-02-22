#pragma once
#include "Plant.h"
#include "Zombie.h"
#include "pea.h"
#include "Timer.h"

class Attack_Plants : // ��� �� ������� �����������
	public Plant
{
protected:

	int HP;
	int damage;
	Timer time_to_shoot;
	sf::Sound s;
public:
	Attack_Plants(sf::Vector2f pos)
		:Plant(5, 50), s(Res_Manager::get().get_access<sf::SoundBuffer>("pusomnadavil.mp3")), time_to_shoot(2000)
	{
		damage = 1;
		isactive = false;
		this->SetPos(pos);
		sprite.setPosition(pos);
		sprite.setTexture(Res_Manager::getmger()->get_access<sf::Texture>("ppss.jpg"));
		sprite.setScale(0.15, 0.2);

		if (Config_load::getconfig().get().at("SoundOn").get<int>())
			s.play();
	}
	// ������������ ����� Plant
	virtual void Update() override;

	virtual void SendMSG(MSG* msg) override;

	virtual void Draw(sf::RenderWindow& win) override;
};