#pragma once
#include "PlaceToPlant.h"
#include "gologram.h"
#define MAX_LINE_WIDTH_X 1500


template<int size>
class Line
{
	sf::Vector2f position;
	std::array<sf::Vector2f, 2> begin_end_points;
	sf::RectangleShape shape;
	std::array<Landing_place*, size> places;
public:
	Line(unsigned index, std::array<bool, size> flag)
	{
		this->position = sf::Vector2f{ BEGIN_OF_LINE_X, float(BEGIN_OF_LINE_Y + index * WIDTH_OF_PLACE) };
		this->shape.setPosition(position);
		shape.setSize({ LINE_WIDTH , WIDTH_OF_PLACE + 2 * PLACE_SEC_Y });
		shape.setFillColor(sf::Color::Yellow);

		this->begin_end_points[0] = { float(BEGIN_OF_LINE_X), float(BEGIN_OF_LINE_Y + index * WIDTH_OF_PLACE - WIDTH_OF_PLACE / 2.0) };
		this->begin_end_points[1] = { float(BEGIN_OF_LINE_X + size * WIDTH_OF_PLACE), float(BEGIN_OF_LINE_Y + index * WIDTH_OF_PLACE - WIDTH_OF_PLACE / 2) };

		for (int index = 0; index < size; index++)
			places[index] = new Landing_place(index, position, flag[index]);
	}

	~Line()
	{
		for (auto pl : places)
			delete pl;
	}

	void Plant(Gologram* g)
	{
		for (Landing_place* P_l : places)
			if (g->getbound().intersects(P_l->getBounds()))
				P_l->ChangePlacMode();
	}

	void Draw(sf::RenderWindow& win);
};

template<int size>
void Line<size>::Draw(sf::RenderWindow& win)
{
	win.draw(shape);
	for (auto pl : places)
		pl->Draw(win);
}
