#pragma once
#include "I_Object.h"
class Test :
    public Object
{
    virtual int Serialize() { return (int)Serialize_Enum::Test; }
    // Унаследовано через Object
    void Update() override;
    void SendMSG(MSG* msg) override;
    void Draw(sf::RenderWindow& win) override;
};

