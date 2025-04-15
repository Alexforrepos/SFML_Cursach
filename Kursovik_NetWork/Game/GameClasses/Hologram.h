#pragma once
#include "./../../Engine/Object.h"

class Hologram : public Object
{
public:
	
private:
//	HoloType holotype;
	sf::Sprite sprite;

	
    void update() override;
    void sendMsg(MSG* msg) override;
    void draw(sf::RenderWindow& win) override;
    sf::Vector2f getPos() override;
    void changePos(const sf::Vector2f& other) override;
    void setPos(sf::Vector2f other) override;
    std::vector<char> serialize() override { return {}; }
    std::pair<Types, std::pair<void*, int>> deserialize(std::vector<char>, size_t&) override { return {}; }
};

