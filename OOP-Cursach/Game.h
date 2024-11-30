#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "O_Manager.h"
#include <string>
#include "Menu.h"

class Game
{
	enum class RUNMODE
	{
		RUNMODE_MENU,
	};

	static Menu m;
	static RUNMODE rm;

	void main_beh_tree(sf::RenderWindow& win);

	void change_mode(const RUNMODE& rm) { this->rm = rm; };


public:
	Game(std::string res_filename);

	void operator()(sf::RenderWindow& win);
};