#pragma once
#include "I_Object.h"
#include "Surface.h"
#include "EnemyManager.h"
class Level :
    public Object
{
    EnemyManager e_m;
    Surface s;

public:


    Level(const EnemyManager& e_m, const Surface& s)
        : e_m(e_m), s(s)
    {

    }

    // Унаследовано через Object
    void Update() override;
    void SendMSG(MSG* msg) override;
    void Draw(sf::RenderWindow& win) override;
};

