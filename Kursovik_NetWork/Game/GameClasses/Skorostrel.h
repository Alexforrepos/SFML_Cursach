#pragma once
#include "Plant.h"
#include "./../../Engine/Object.h"
#include <SFML/Graphics.hpp>
#include "./../Utils/Timer.h"

class Skorostrel :
	public Plant
{
	sf::Sprite sprite;
	Timer clickTimer;
	std::string plantType;

public:

	//не использовать!!! нужно для сериализации
	Skorostrel() = default;

	Skorostrel(const std::string& plantType, sf::Vector2f pos);


	void update() override;
	void sendMsg(Engine::MSG* msg) override;
	void draw(sf::RenderWindow& win) override;
	sf::Vector2f getPos() override;
	void changePos(const sf::Vector2f& other) override;
	void setPos(sf::Vector2f other) override;

	

};