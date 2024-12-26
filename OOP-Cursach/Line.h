#pragma once
#include "PlaceToPlant.h"


class Line :
	public Object
{

protected:
	sf::Rect<float> intershape;

	std::vector<PlaceToPlant*> places;

public:
	Line() = default;

	Line(int nomer, int size)
	{
		this->Position.x = BEGIN_OF_LINE_X + WIDTH_OF_PLACE;
		this->Position.y = BEGIN_OF_LINE_Y + nomer * WIDTH_OF_PLACE;

		for (int i = 0; i < size; i++)
		{
			this->places.push_back(new PlaceToPlant());
		}
	}


	// Унаследовано через I_Object
	void Update() override;

	void SendMSG(MSG* msg) override;

	void Draw(sf::RenderWindow& win) override;

};