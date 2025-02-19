#pragma once
#include "Plant.h"
#include "Zombie.h"
#include "pea.h"
#include "Timer.h"

class Attack_Plants : // так же обычный горохострел
    public Plant
{
protected:

    int HP;
    int damage;
    Timer time_to_shoot;
    sf::Sound s;
public:
    Attack_Plants(sf::Vector2f pos)
        :s(Res_Manager::get().get_access<sf::SoundBuffer>("pusomnadavil.mp3")),time_to_shoot(2000)
    {
        damage = 1;
        HP = 5;
        isActive = false;
        this->SetPos(pos);
        sprite.setPosition(pos);
        sprite.setTexture(Res_Manager::getmger()->get_access<sf::Texture>("ppss.jpg"));
        sprite.setScale(0.15, 0.2);

        s.play();
    }
    // ”наследовано через Plant
    virtual void Update() override;

    virtual void SendMSG(MSG* msg) override;

    virtual void Draw(sf::RenderWindow& win) override;
};