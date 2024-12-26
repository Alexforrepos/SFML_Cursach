#pragma once
#include "Plant.h"

class Attack_Plants : // так же обычный горохострел
    public Plant
{
protected:
    int damage,cd_time_ms;
    sf::Clock time_to_shoot;
public:
    // ”наследовано через Plant
    virtual void Update() override;

    virtual void SendMSG(MSG* msg) override;

    virtual void Draw(sf::RenderWindow& win) override;

};

