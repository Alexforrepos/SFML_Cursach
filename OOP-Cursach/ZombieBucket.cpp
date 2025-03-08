#include "ZombieBucket.h"
#include "ResourceManager.h"
#include "MSG_Manager.h"
#include "pea.h"

ZombieBucket::ZombieBucket() : Zombie() 
{
    armor = 5;
    sprite.setTexture(Res_Manager::getmger()->get_access<sf::Texture>("IvtClub.png"));
}

void ZombieBucket::SendMSG(MSG* msg) 
{
    if (msg->MSG_TYPE.index() == (int)MSG_TYPE::MSG_TYPE_MOVE)
    {
        if (MSG_TYPE_MOVE(*msg).obj->Serialize() == (int)Serialize_Enum::Pea)
        {
            pea* p = static_cast<pea*>(MSG_TYPE_MOVE(*msg).obj);
            if (p->GetBound().intersects(this->getBounds()))
            {

                MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(p, this)));
            }
        }
        else 
        { 
            Zombie::SendMSG(msg);
        }
        return;
    }
   if (msg->MSG_TYPE.index() == (int)MSG_TYPE::MSG_TYPE_DEAL_DAMAGE)
    {
        if (MSG_TYPE_DEAL_DAMAGE(*msg).target == this) 
        {
            int damage = MSG_TYPE_DEAL_DAMAGE(*msg).damage;
            if (armor > 0)
            {
                armor -= damage;
                if (armor <= 0) 
                {
                    armor = 0;
                    sprite.setTexture(Res_Manager::getmger()->get_access<sf::Texture>("zombie_n.png"));
                }
            }
            else 
            {
                HP -= damage;
                if (HP <= 0) 
                {
                    HP = 0;
                    MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(this, this)));
                }
            }
        }
        return;
    }
       Zombie::SendMSG(msg);
}
