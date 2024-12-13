#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Line.h"
class Surface
	:I_Object
{
	sf::Shape* s;
	std::vector<Line*> Lines;
public:
	Surface() = default;

	Surface(sf::Shape* s, const std::vector<Line*>& Lines)
		: s(s), Lines(Lines)
	{
	}

	// Унаследовано через I_Object
	void Update() override;
	void SendMSG(MSG* msg) override;
	void Draw(sf::RenderWindow& win) override;
};