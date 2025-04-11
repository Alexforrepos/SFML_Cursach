#pragma once
#define ZOMBIE_ENUM_RANGE 12
#define CART_SIZE_W 50
#define CARD_SIZE_H 100
#include "./../../Engine/Object.h"



class Cart :
    public Object
{
public:
    enum class HoldType
    {
        Peashooter = 1,
        
        
        
        
        
        
        
        
        
        
        Zombie = ZOMBIE_ENUM_RANGE
    };

private:
    HoldType holdtype;

    sf::RectangleShape interShape;

    Object* hologram;
    
    uint16_t cost;
public:
    
    

    Cart(const HoldType& holdtype, const sf::RectangleShape& interShape, Object* hologram, const uint16_t& cost)
        : holdtype(holdtype), interShape(interShape), hologram(hologram), cost(cost), Object(int(Types::Cart))
    {
        
    }

   

    // Унаследовано через Object
    sf::Vector2f getPos() override;

    void changePos(const sf::Vector2f& other) override;

    void setPos(sf::Vector2f other) override;

    std::vector<char> serialize() override;

    std::pair<Types, std::pair<void*, int>> deserialize(std::vector<char> data, size_t& readpoint) override;

    void update() override;

    void draw(sf::RenderWindow& win) override;

    void sendMsg(MSG* msg) override;

};

