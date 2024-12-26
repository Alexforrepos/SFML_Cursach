#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>
#include "Line.h"
#include "WaterLine.h"
#define NORMAL_QUANT_LINE 8



class Surface
	:Object
{

	sf::Shape* s;
	sf::Sprite* spr;
	std::vector<Line*> Lines;


public:
	Surface() = default;

	Surface(std::array<bool, 6> boolwaterlevelmask,int size)
	{
		int i = 0;
		for (auto mask : boolwaterlevelmask)
		{
			
			if (mask)
			{
				//Lines.push_back(new WaterLine());
			}
			else
			{
				//Lines.push_back(new Line(i,8));
			}
			i++;
		}
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
	
	// Унаследовано через I_Object
	void Update() override;
	void SendMSG(MSG* msg) override;
	void Draw(sf::RenderWindow& win) override;
};