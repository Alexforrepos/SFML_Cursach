#pragma once
#include <iostream>
#include <vector>
#include <array>
#include "Line.h"
#include "I_Object.h"
#include "gologram.h"
#include "Zombie.h"

//�������� �����
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
	~Surface()
	{
		for (auto line : Lines)
			delete line;
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
	void Wrest(Plant* pl)
	{
		for (auto line : Lines)
		{
			line->Wrest(pl);
		}
	}

	void Plant(Object* obj);
	void CheckCollision(Zombie *zombie)
	{
		for (auto line : Lines)
		{
			line->CheckCollision(zombie);
			if (line->getbound().intersects(zombie->getBounds()))
			{
				line->Activate();
			}
		}
	}
	void deactivateLines(Zombie * zombie)
	{
		for (auto line : Lines)
		{
			line->CheckCollision(zombie);
			if (line->getbound().intersects(zombie->getBounds()))
			{
				line->Deactivate();
			}
		}
	}
};

template<int place_size, int line_count>
inline void Surface<place_size, line_count>::Plant(Object* obj)
{
	Hologram* g = (Hologram*)obj;
	for (auto line : Lines)
		if (line->Plant_(g))
			return;
}
