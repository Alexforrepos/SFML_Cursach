#pragma once
#include "Plant.h"
#include "Zombie.h"

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
        HP = 5;
        this->SetPos(pos);
        sprite.setPosition(pos);
        sprite.setTexture(*Res_Manager::getmger()->get_access<sf::Texture*>("pps.jpg"));
        sprite.setScale(0.23, 0.18);
    }
    // ”наследовано через Plant
    virtual void Update() override;

    virtual void SendMSG(MSG* msg) override;

    virtual void Draw(sf::RenderWindow& win) override;
};

