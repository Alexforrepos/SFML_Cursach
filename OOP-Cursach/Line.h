#pragma once
#include "PlaceToPlant.h"
#define MAX_LINE_WIDTH_X 1500


template<int size>
class Line 
{
	sf::Vector2f position;
	std::array<sf::Vector2f, 2> begin_end_points;
	sf::RectangleShape shape;
	std::vector<Landing_place*> places;	
public:
	Line(unsigned index,std::array<bool,size> flag)
	{
		this->position(BEGIN_OF_LINE_X, BEGIN_OF_LINE_Y + index * WIDTH_OF_PLACE);
		this->shape.setPosition(position);
		shape.setSize(WIDTH_OF_PLACE * size, WIDTH_OF_PLACE);
		shape.setFillColor(sf::Color::Yellow);

		this->begin_end_points[0] = { BEGIN_OF_LINE_X , BEGIN_OF_LINE_Y + index * WIDTH_OF_PLACE - WIDTH_OF_PLACE / 2 };
		this->begin_end_points[1] = { BEGIN_OF_LINE_X + size * WIDTH_OF_PLACE, BEGIN_OF_LINE_Y + index * WIDTH_OF_PLACE - WIDTH_OF_PLACE / 2 };

		for (int index = 0; i < size; i++)
			places[index] = new Landing_place(index, position, flag[index]);
	}

	~Line()
	{
		for (auto pl : places)
			delete pl;
	}
};