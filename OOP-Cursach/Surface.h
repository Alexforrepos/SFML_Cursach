#pragma once
#include <iostream>
#include <vector>
#include <array>
#include "Line.h"
#include "I_Object.h"
#include "gologram.h"

//коллизия зомби
template<int place_size,int line_count>
class Surface
{

	sf::RectangleShape s;	
	std::array<Line<place_size>*,line_count> Lines; 


public:
	Surface()
	{
		for (int i = 0; i < line_count; i++)
			Lines[i] = new Line<place_size>(i, { 0 });
	}

	int GetPower() 
	{
		int power = 0;
		for (auto l:Lines)
		return power;
	}
	
	void Draw(sf::RenderWindow& win)
	{
		win.draw(s);
		for (auto line : Lines)
			line->Draw(win);

	}

	void Plant(Object* obj);
	void CheckCollision(Zombie *zombie)
	{
		for (auto line : Lines)
		{
			line->CheckCollision(zombie);
		}
	}
};

template<int place_size, int line_count>
inline void Surface<place_size, line_count>::Plant(Object* obj)
{
	Gologram* g = (Gologram*)obj;
	for (auto line : Lines)
		line->Plant_(g);
}
