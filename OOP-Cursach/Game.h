#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "O_Manager.h"
#include <string>
#include "Menu.h"



class Game
{
	static Game* game;

	enum class RUNMODE
	{
		RUNMODE_MENU, RUNMODE_GAME
	};

	bool isRun;

	static RUNMODE rm;

	void change_mode(const RUNMODE& rm) { this->rm = rm; };

	sf::RenderWindow win;

	Game(std::string res_filename);

	O_Manager& OMg;
	Res_Manager& RMg;
	MSG_Manager& MsMg;

public:
	void Run();

	static Game* Get() 
	{
		return game ? game : game = new Game("./resources/res_list.txt");
	}

	static void Del() 
	{
		if (game)
			delete game;
	}

	bool isRunning();

	void operator()(sf::RenderWindow& win);
};