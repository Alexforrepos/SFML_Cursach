#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "O_Manager.h"
#include <string>
#include "Menu.h"
#include ".\..\Lib\Json\include\nlohmann\json.hpp"



class Game
{
public:
	enum class RUNMODE
	{
		RUNMODE_MENU, RUNMODE_GAME
	};
private:
	static Game* game;
	

	friend class Game_Proc;
	friend class Menu;

	bool isRun;
	nlohmann::json Config;

	RUNMODE rm, lastrm;

	sf::RenderWindow win;

	Game(std::string res_filename);

	void Close()
	{
		OMg.clear();
		MsMg.clear();

		isRun = false;
	}

	O_Manager& OMg;
	Res_Manager& RMg;
	MSG_Manager& MsMg;

	void Start(std::string jsonname)
	{
		std::fstream file(jsonname);
		if (!file.is_open())
		{
			throw "json file didnt open";
		}
		file >> Config;
		file.close();
	}

public:

	static Game& Get()// Game::Get()
	{
		return game ? *game : *(game = new Game("./resources/res_list.txt"));
	}

	static void Del() 
	{
		if (game)
			delete game;
	}

	void Run();

	const bool& GetConfig(std::string confname);//{ if (Config.is) };

	void ChangeRunMode(RUNMODE RM) { lastrm = rm; this->rm = RM; }
	void SetRM() { this->lastrm = rm; }

	inline bool isRunning() {return isRun;}

	int GetRunMod() { return int(rm); }
};