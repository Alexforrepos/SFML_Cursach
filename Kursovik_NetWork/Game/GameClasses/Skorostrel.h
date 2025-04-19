#pragma once
#include "./../../Engine/Object.h"
#include <SFML/Graphics.hpp>
#include "./../Utils/Timer.h"

class Skorostrel :
	public Object<Skorostrel>
{
	sf::Sprite sprite;
	Timer clickTimer;
	std::string plantType;

public:
	Skorostrel(const std::string& plantType, sf::Vector2f pos);


	void update() override;
	void sendMsg(MSG* msg) override;
	void draw(sf::RenderWindow& win) override;
	sf::Vector2f getPos() override;
	void changePos(const sf::Vector2f& other) override;
	void setPos(sf::Vector2f other) override;

};