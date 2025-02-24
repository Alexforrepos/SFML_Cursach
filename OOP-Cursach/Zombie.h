#pragma once
#include "I_Object.h"
#include "MSG_Manager.h"
#include "ResourceManager.h"
#include "Timer.h"
#include "pea.h"
#include "Effect.h"
#include "PlaceToPlant.h"
#include "Config_load.h"

class Plant;
class Zombie // обычный зомби
    : public Object
{
    friend class Effect;
    Timer timer;
protected:
    int HP, cd_time_mc, height;
    sf::Sprite sprite;
    sf::Clock cd_time;
    sf::Vector2f damage_area_size;
    sf::Vector2f Size = { 100,100 };
    std::pair<sf::Vector2f, sf::Vector2f> traectory;
    Plant* target;
    bool is_attack;
    //
    std::vector<Effect*> eff;
public:
    Zombie()
        : timer(1000), cd_time(), damage_area_size(100, 100), is_attack(false), height(0), HP(5), cd_time_mc(300), target(nullptr)
    {
        sprite.setTexture(Res_Manager::getmger()->get_access<sf::Texture>("zombie_n.png"));
        sprite.setScale(0.1, 0.15);
        Size = sf::Vector2f{ 100, 100 };

      
        const float possibleLines[] = { BEGIN_OF_LINE_Y , BEGIN_OF_LINE_Y + WIDTH_OF_PLACE * 2, BEGIN_OF_LINE_Y + 2 * WIDTH_OF_PLACE * 2 };
        const int numLines = sizeof(possibleLines) / sizeof(possibleLines[0]);       
        float randomLine = possibleLines[rand() % numLines];

        sprite.setPosition({ 1500.f, randomLine });
        this->SetPos({ 1500.f, randomLine });
        if (Config_load::getconfig().get().at("ZombieImmortal").get<int>())
            HP += 10000;
    }

    //
    Zombie(std::pair<sf::Vector2f, sf::Vector2f> traectory)
        : Zombie()
    {
        this->traectory = traectory;
    }

    void StartAttack(Plant* plant);
    void StopAttack();

    // ”наследовано через Object
    virtual void Update();
    virtual void SendMSG(MSG* msg);
    int Serialize() override
    {
        return (int)Serialize_Enum::Zombie;
    }
    virtual void Draw(sf::RenderWindow& win);

    sf::FloatRect getBounds() { return { Position.x, Position.y, Size.x, Size.y }; }
};