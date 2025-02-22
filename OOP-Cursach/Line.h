#pragma once
#include "PlaceToPlant.h"
#include "gologram.h"
#include "Zombie.h"
#include "Attack_Plants.h"
#include "Repeater.h"
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

	int Plant_(Hologram* g)
	{
		Plant* PlacedPlant = nullptr;
		for (Landing_place* P_l : places)
		{
			{
				if (g->getType() == HoloType::Showel && g->getbound().intersects(P_l->getBounds()))
				{
					if (P_l->GetPlant())
						MSG_Manager::getmger()->add(new MSG(MSG_TYPE_KILL(P_l->GetPlant(), g)));
					P_l->Wrest();
					return 1;
				}
			}
			if (g->getbound().intersects(P_l->getBounds()) && !P_l->IsPlanted() && P_l->Isplacable())
			{

				switch (g->getType())
				{
				case Peashooter:
					P_l->Plant_(PlacedPlant = new Attack_Plants(P_l->getBounds().getPosition()));
					MSG_Manager::getmger()->add(new MSG(MSG_TYPE_CREATE(PlacedPlant, g)));
					break;
				case Sunflower:
					break;
				case MrBigPenis:
					break;
				case Repeater:
					P_l->Plant_(PlacedPlant = new Repeater(P_l->getBounds().getPosition()));
					MSG_Manager::getmger()->add(new MSG(MSG_TYPE_CREATE(PlacedPlant, g)));
					break;
					break;
				default:
					break;
				}

				return 1;
			}
		}
		return 0;
	}

	void Draw(sf::RenderWindow& win);
	void CheckCollision(Zombie* zombie)
	{
		for (Landing_place* P_l : places)
		{
			if (P_l->IsPlanted() && P_l->getBounds().intersects(zombie->getBounds()))
			{
				zombie->StartAttack(P_l->GetPlant());
				break;
			}
		}
	}

	void Wrest(Plant* pl)
	{
		for (auto P_l : places)
		{
			if (P_l->GetPlant() == pl)
				P_l->Wrest();
		}
	}

	sf::Rect<float> getbound()
	{
		return shape.getGlobalBounds();
	}

	void Activate();
	void Deactivate();
};

template<int size>
void Line<size>::Draw(sf::RenderWindow& win)
{
	win.draw(shape);
	for (auto pl : places)
		pl->Draw(win);
}

template<int size>
inline void Line<size>::Activate()
{
	for (auto pl : places)
	{
		if (pl->IsPlanted())
			pl->GetPlant()->setActivity(true);
	}
}

template<int size>

inline void Line<size>::Deactivate()
{
	for (auto pl : places)
	{
		if (pl->IsPlanted())
			pl->GetPlant()->setActivity(false);
	}
}