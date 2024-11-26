#pragma once
#include "I_Object.h"

class DEBUG_CLASS :
    public I_Object
{
public:
    DEBUG_CLASS()
        : I_Object()
    {
        std::cout << "DEBUG CLASS CREATED\n";
    }
    ~DEBUG_CLASS() 
    {
        std::cout << "DEBUG CLASS DESTRUCT" << std::endl;
    }
    // Унаследовано через I_Object
    void Update() override;
    void SendMSG(MSG* msg) override;
    void Draw(sf::RenderWindow& win) override;
};

