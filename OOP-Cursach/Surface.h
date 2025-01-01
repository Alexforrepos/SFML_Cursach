#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>
#include "Line.h"
#define NORMAL_QUANT_LINE 8



template<int place_size>
class Surface
{

	sf::RectangleShape s;
	std::vector<Line<place_size>*> Lines;


public:
	Surface() = default;

	Surface(unsigned Line_size = 1)
	{
		for (int i = 0; i < Line_size; i++)
			Lines[i] = new Line<place_size>(i, { 0 });
	}

	Surface(sf::Shape* s, const std::vector<Line*>& Lines)
		: s(s), Lines(Lines)
	{

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
};