#pragma once
#include "I_Object.h"
class Effect :
    public Object
{
    sf::Clock effecttime; // для отслеживания времени эффекта
    int durity_asmill; // длительность эффекта в миллисекудах
public:
    
    sf::Clock& time() { return effecttime; }
    void restart() { effecttime.restart(); }
};