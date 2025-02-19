#pragma once
#include <SFML/Graphics.hpp>

//класс предназначенный для счета периодического времени
class Timer
{
	sf::Clock timer;
	int time_d;
	
public:
	//возвращает прошло ли времени больше чем кд
	bool operator()(void)
	{
		return timer.getElapsedTime().asMilliseconds() > time_d;
	}
	

	Timer(int time_d)
		: timer(), time_d(time_d)
	{
	}
	//заставляет считать заново таймер
	void restart() { timer.restart(); }
};

