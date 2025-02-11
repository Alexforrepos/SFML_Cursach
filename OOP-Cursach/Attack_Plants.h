#pragma once
#include "Plant.h"
#include "Zombie.h"
#include "pea.h"

class Attack_Plants : // так же обычный горохострел
    public Plant
{
protected:

    int HP;
    int damage,cd_time_ms;
    sf::Clock time_to_shoot;
public:
    Attack_Plants(sf::Vector2f pos)
    {
        cd_time_ms = 1000;
        damage = 1;
        HP = 5;
        this->SetPos(pos);
        sprite.setPosition(pos);
        sprite.setTexture(*Res_Manager::getmger()->get_access<sf::Texture*>("ppss.jpg"));
        sprite.setScale(0.15, 0.2);

        Res_Manager::get().get_access<sf::Music*>("pusomnadavil.mp3")->play();
    }
    // ”наследовано через Plant
    virtual void Update() override;

    virtual void SendMSG(MSG* msg) override;

    virtual void Draw(sf::RenderWindow& win) override;
};

