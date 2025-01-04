#include "Zombie.h"
#include "Plant.h"


void Zombie::Update()
{
    if (is_attack)
    {
        if (this->timer())
        {
            MSG_Manager::getmger()->add(new MSG(MSG_TYPE_DEAL_DAMAGE(target, this, 10)));
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
}

void Zombie::SendMSG(MSG* msg)//проверка на движенме гороха
{
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
    
    if (msg->MSG_TYPE.index() == (int)MSG_TYPE::MSG_TYPE_MOVE)
    {
        
        if (MSG_TYPE_MOVE(*msg).obj->Serialize() == (int)Serialize_Enum::Pea)
        {
         if (((pea*)(MSG_TYPE_MOVE(*msg).obj))->GetBound().intersects(this->getBounds()))
            MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(this, this)));
        }
    }

    if (msg->MSG_TYPE.index() == (int)MSG_TYPE::MSG_TYPE_KILL)
    {
        if (MSG_TYPE_KILL(*msg).victim == this->target)
        {
            this->StopAttack();
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
