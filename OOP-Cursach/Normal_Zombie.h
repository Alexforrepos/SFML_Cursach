#pragma once
#include "Zombie.h"
#define NORMAL_ZOMBIE_HP 120



class Normal_Zombie :
    public Zombie
{
    
public:
    Normal_Zombie(Line* line)
    {
        this->line = line;
        this->surface_level = 0;
        this->HP = NORMAL_ZOMBIE_HP;
    }

    // Унаследовано через Zombie
    virtual void Update();

    virtual void SendMSG(MSG* msg);

    virtual void Draw(sf::RenderWindow& win);

};

