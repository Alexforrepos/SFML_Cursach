#pragma once
#include "I_Object.h"
#include "Timer.h"
class Effect :
    public Object
{
    Timer time_to_die;
    class Object* target;
public:

    
    // Унаследовано через Object
    void Update() override;

    void SendMSG(MSG* msg) override;

    void Draw(sf::RenderWindow& win) override;

    Effect(const Timer& time_to_die, Object* target)
        : time_to_die(time_to_die), target(target){};

    inline int Serialize() { return int(Serialize_Enum::Effect); }
    
    void effect() {};

    Effect() = default;
};