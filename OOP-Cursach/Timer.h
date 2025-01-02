#pragma once
#include <SFML/Graphics.hpp>
class Timer
{
	sf::Clock timer;
	int time_d;
	
public:
	bool operator()(void)
	{
		return timer.getElapsedTime().asMilliseconds() > time_d;
	}
	

	Timer(int time_d)
		: timer(), time_d(time_d)
	{
	}

	void restart() { timer.restart(); }
};

