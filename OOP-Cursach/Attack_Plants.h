#pragma once
#include "Plant.h"

class Attack_Plants : // так же обычный горохострел
    public Plant
{
protected:
    int damage,cd_time_ms;
    sf::Clock time_to_shoot;
public:
    Attack_Plants(sf::Vector2f pos)
    {
        this->SetPos(pos);
        sprite.setPosition(pos);
        sprite.setTexture(*Res_Manager::getmger()->get_access<sf::Texture*>("00_6.png"));
        sprite.setScale(1, 1);
    }
    // ”наследовано через Plant
    virtual void Update() override;

    virtual void SendMSG(MSG* msg) override;

    virtual void Draw(sf::RenderWindow& win) override;

};

