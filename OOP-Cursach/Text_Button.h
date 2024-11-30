#pragma once
#include "Button.h"
class Text_Button :
    public Button
{
    sf::Text t;
    
public:


    // Унаследовано через Button
    void Update() override;

    void SendMSG(MSG* msg) override;

    void Draw(sf::RenderWindow& win) override;

};

