#pragma once
#include "I_Object.h"
#include <functional>

class Button :
    public Object 
{
    bool is_active;

    sf::RectangleShape Intershape;
    std::function<void(void)> f;

    sf::Color active, passive;

public:
      
    // Унаследовано через I_Object
    virtual void Update() override;

    virtual void SendMSG(MSG* msg) override;

    virtual void Draw(sf::RenderWindow& win) override;

};

