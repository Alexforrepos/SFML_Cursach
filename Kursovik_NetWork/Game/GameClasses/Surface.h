#pragma once
#include "./../../Engine/Object.h"
#include "./../../Engine/MSG_Manager.h"
#define DEFAULT_LINE_QOUNT 5
#define DEFAULT_LINE_SIZE 10
#define START_SURFACE_POSITION_X 300
#define START_SURFACE_POSITION_Y 100
#define PLANT_DISTANCE 20
#define PLANT_SIZE_W 100
#define PLANT_SIZE_H 100



/// <summary>
/// класс линий и мест отвечает за расмещение расстений по местам
/// </summary>
class Surface
	: public Object
{
	int lines_qount, lines_size;

	
	struct Place
	{
		bool isplanted;
		Object* plant_;
		sf::Rect<float> shape_rect;


		Place(sf::Vector2f pos, sf::Vector2f size)
			:shape_rect(pos, size), isplanted(false), plant_(nullptr)
		{

		}

		void plant(Object* plant_)
		{
			if (isplanted)
				return;
			this->plant_ = plant_;
			this->isplanted = true;
		}

		void deletePLant()
		{
			if (!isplanted)
				return;
			isplanted = false;
			MSG_Manager::get().addMSG(std::shared_ptr<MSG>(new MSG_TYPE_KILL(plant_, nullptr)));
		}

		bool isPlanted()
		{
			return isplanted;
		}

		void draw(sf::RenderWindow& win)
		{

			sf::RectangleShape renshape(shape_rect.getSize());
			renshape.setPosition(shape_rect.getPosition());
			renshape.setFillColor(isplanted ? sf::Color::Cyan : sf::Color::Green);
			win.draw(renshape);
		}
	};

	std::vector<std::vector<Place>> place_vector;

public:
	Surface(const int& lines_qount = DEFAULT_LINE_QOUNT, const int& lines_size = DEFAULT_LINE_SIZE)
		:lines_qount(lines_qount), lines_size(lines_size), Object(static_cast<int>(Types::Level))
	{
		for (int rows = 0; rows < lines_qount; rows++)
		{
			place_vector.push_back(std::vector<Place>());
			for (int cols = 0; cols < lines_size; cols++)
			{
				place_vector[rows].push_back(Place({
			   static_cast<float>(START_SURFACE_POSITION_X + cols * (PLANT_SIZE_W + PLANT_DISTANCE)),
					static_cast<float>(START_SURFACE_POSITION_Y + rows * (PLANT_SIZE_H + PLANT_DISTANCE)) },
					{ PLANT_SIZE_W,PLANT_SIZE_H }));
			}
		}
	}



	// Унаследовано через Object
	sf::Vector2f getPos() override;

	void changePos(const sf::Vector2f& other) override;

	void setPos(sf::Vector2f other) override;

	void update() override;

	void draw(sf::RenderWindow& win) override;

	void sendMsg(MSG* msg) override;

};

