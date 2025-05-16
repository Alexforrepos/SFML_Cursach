#pragma once
#include "Engine/O_Manager.h"
#include "GameClasses/Effect.h"
#include "Utils/Config.h"
#include "Utils/Timer.h"

class Zombie
    : public Object
{
    friend class Effect;
    sf::Vector2f pos;
    uint16_t HP,
        velocity, // =speed 
        damage,
        line;
    sf::Sprite spr;
    bool isAttack;
    std::vector<EffectPtr> effects;
    Timer time;
public:
    Zombie() = default;
    Zombie(const uint16_t& HP, const uint16_t& velocity, const uint16_t& damage, const uint16_t& line, std::string textureId)
        :Object(int(Types::BaseZombieType)), HP(HP), velocity(velocity), damage(damage), line(line), isAttack(false)
    {
        spr.setTexture(R_Manager::get().access<sf::Texture>(textureId));
    }
    Zombie(const uint16_t& line)
        :Zombie(
            Config::getInstance()["ZombieParams"]["Zombies"]["Zombie"]["HP"],
            Config::getInstance()["ZombieParams"]["Zombies"]["Zombie"]["Speed"],
            Config::getInstance()["ZombieParams"]["Zombies"]["Zombie"]["Damage"],
            line, "bullet.png")
    {
        spr.setScale(0.1f, 0.1f);
    }
    void draw(sf::RenderWindow& win)
    {
        win.draw(spr);
    }
    sf::Vector2f getPos() { return pos; }
    sf::Vector2f setPos(const sf::Vector2f& pos) { spr.setPosition(pos); }
    void changePos(sf::Vector2f& pos) 
    {
        this->pos.x -= velocity;
        spr.setPosition(pos);
    }
    void update() override
    {
        if (isAttack)
        {
            if (this->time())
            {
                //MSG_Manager::get().addMSG(std::make_shared<Engine::MSG_TYPE_KILL>(this, damage_msg->damager.get()); //он ждёт лучших времён
                std::cout << "PALITIKAA!!!" << std::endl;
            }
        }
        if (time() && !isAttack)
        {
            changePos(pos);
        }
        for (auto effect = effects.begin(); effect != effects.end(); )
        {
            if ((*effect)->tick(*this))
            {
                effect++;
            }
            else
            {
                effect = effects.erase(effect);
            }
        }
        return;
    }
    void sendMsg(const std::shared_ptr<Engine::MSG>& msg) override
    {

    }
    void addEffect(const EffectPtr& eff)
    {
        effects.push_back(eff);
    }
    void removeEffect(const EffectPtr& eff = nullptr)
    {
        if (!eff)
        {
            effects.clear();
        }
        else
        {
            effects.erase(std::remove(effects.begin(), effects.end(), eff), effects.end());
        }
    }
};