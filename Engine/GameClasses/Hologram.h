#pragma once
#include "Engine/Object.h"
#include "Engine/MSG_Manager.h"
#include "GameClasses/Plant.h"
#include <SFML/Graphics.hpp>
#include "Utils/Timer.h"
#include "Engine/R_Manager.h"
#include "Engine/O_Manager.h"
#include "PeaShooter.h"
#include "Apex.h"

class Hologram :
    public Object
{
private:
   sf::Sprite sprite;
    std::string plantType; 
    Timer Clicktime;
    sf::Vector2f position;
    bool wasRightPressed = false;
public:	
    Hologram()
        :Clicktime(500)
    {
        Clicktime.restart();
    };

    Hologram(const sf::Vector2f& startPos, const std::string& type);
    void update() override;
    void sendMsg(const std::shared_ptr<Engine::MSG>& msg) override;
    void draw(sf::RenderWindow& win) override;
    sf::Vector2f getPos() override;
    void changePos(const sf::Vector2f& other) override;
    void setPos(sf::Vector2f other) override;
    const std::string& getPlantType() const { return plantType; }
    Types ObjectType;

    sf::FloatRect getRect() { return { position.x,position.y,30,30 }; }
    ~Hologram()
    {
    
    };
   
};