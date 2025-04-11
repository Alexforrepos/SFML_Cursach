#pragma once
#include "./../../Engine/Object.h"
#include "./../../Engine/R_Manager.h"
#include "./../Utils/Config.h"
#include "./../Utils/Timer.h"
enum CartType

{
	Peashooter, Repeater, Sunflower, Potato, Apex, Cactus, IceShooter, Zombie, MiniZombie, HelmZombie, PaperZombie, ZombieShooter
};

class Cart
	: public Object
{
	CartType Tp;
	sf::Sprite spr;
	Timer timer;
public:
	
};
