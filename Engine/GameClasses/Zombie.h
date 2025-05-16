#pragma once
#include "Engine/O_Manager.h"
#include "GameClasses/Effect.h"

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
    std::vector<EffectPtr> effects_;
public:
    Zombie(const uint16_t& HP, const uint16_t& velocity, const uint16_t& damage, const uint16_t& line, const sf::Sprite& spr)
        :Object(int(Types::BaseZombieType)), HP(HP), velocity(velocity), damage(damage), line(line), spr(spr)
    {
    }
    sf::Vector2f getPos() { return pos; }
    sf::Vector2f setPos(const sf::Vector2f& pos) { this->pos = pos; }
    void changePos(sf::Vector2f& pos) 
    {
        this->pos.x -= velocity;
    }
    void update() override 
    {
        for (auto effect = effects_.begin(); effect != effects_.end(); )
        {
            if ((*effect)->tick(*this)) 
            {
                effect++;  
            }
            else 
            {
                effect = effects_.erase(effect);  
            }
        }
    }
    void sendMsg(const std::shared_ptr<Engine::MSG>& msg) override 
    {

    }
    void addEffect(const EffectPtr& eff) 
    {
        effects_.push_back(eff);
    }
    void removeEffect(const EffectPtr& eff = nullptr)
    {
        if (!eff)
        {
            effects_.clear();
        }
        else 
        {
            effects_.erase(std::remove(effects_.begin(), effects_.end(), eff), effects_.end());
        }
    }
};

/*#include "Zombie.h"
#include "Plant.h"

void Zombie::Update()
{
    if (is_attack)
    {
        if (this->timer())
        {
            MSG_Manager::getmger()->add(new MSG(MSG_TYPE_DEAL_DAMAGE(target, this, 1)));
            timer.restart();
        }
        return;
    }
     
    if (timer() && !is_attack)
    {
        timer.restart();

        sf::Vector2f Move(-5.0, 0.0);
        MSG_Manager::getmger()->add(new MSG(MSG_TYPE_MOVE(Move, this)));
        this->Position += Move;
        sprite.move(Move);
    }

    for (auto ef : eff) ef;
}

void Zombie::SendMSG(MSG* msg)
{
    if (msg->MSG_TYPE.index() == (int)MSG_TYPE::MSG_TYPE_MOVE)
    {
        if (MSG_TYPE_MOVE(*msg).obj->Serialize() == (int)Serialize_Enum::Pea)
        {

            pea* p = static_cast<pea*>(MSG_TYPE_MOVE(*msg).obj);
          
            if (p->GetBound().intersects(this->getBounds()))
            {
              
                HP -= p->getDamage();


                MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(p, p)));


                if (HP <= 0)
                {
                    HP = 0;
                    MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(this, this)));
                }
            }
        }
    }

    if (msg->MSG_TYPE.index() == (int)MSG_TYPE::MSG_TYPE_DEAL_DAMAGE)
    {
        if (MSG_TYPE_DEAL_DAMAGE(*msg).target == this)
        {
            HP -= MSG_TYPE_DEAL_DAMAGE(*msg).damage;
            if (HP <= 0)
            {
                HP = 0;
                MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(this, this)));
            }
        }
    }

    if (msg->MSG_TYPE.index() == (int)MSG_TYPE::MSG_TYPE_KILL)
    {
        if (MSG_TYPE_KILL(*msg).victim == this->target)
        {
            this->StopAttack();
        }
        if (MSG_TYPE_KILL(*msg).victim->Serialize() == int(Serialize_Enum::Effect))
        {
            for (auto it = eff.begin(); it != eff.end(); it++)
            {
                if (*it == MSG_TYPE_KILL(*msg).victim)
                {
                    eff.erase(it);
                    break;
                }
            }
        }
    }
}


void Zombie::StartAttack(Plant * plant)
{
    target = plant;
    is_attack = true;
}

void Zombie::StopAttack()
{
    is_attack = false;
    target = nullptr;
}

void Zombie::Draw(sf::RenderWindow& win)
{
    win.draw(sprite);
    sf::RectangleShape r(Size);
    r.setPosition(Position);
    win.draw(r);
}
*/