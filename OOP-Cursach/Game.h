#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "O_Manager.h"
#include <string>



//основной класс игры 
//предназначен для объединения общеигровых данных 
//изменения состояния игры, иницианилизации окна
//и др.
class Game
{
	friend class Game_Proc;
	friend class Menu;
	friend void EXIT();	
public:
	enum class RUNMODE
	{
		RUNMODE_MENU, RUNMODE_GAME
	};
private:

#pragma region Переменные
	//синглтон
	static Game* game;
	
	bool isRun;
	RUNMODE rm, lastrm;
	sf::RenderWindow win;

	O_Manager& OMg;
	Res_Manager& RMg;
	MSG_Manager& MsMg;
#pragma endregion


	Game(std::string res_filename);
	~Game()
	{
		Res_Manager::del();
		O_Manager::del();
	}

	void Close()
	{
		OMg.clear();
		MsMg.clear();

		isRun = false;
	}
public:
#pragma region Init
	static Game& Get()// Game::Get()
	{
		return game ? *game : *(game = new Game("./resources/res_list.txt"));
	}
	static void Del()
	{
		if (game)
			delete game;
	}
#pragma endregion

	//позволяют понять запущена ли игра
	inline bool isRunning() { return isRun; }
	//основной цикл игры
	void Run();

	//возвращает текущий мод игры
	inline int GetRunMod() { return int(rm); }
	//позволяет окончательно устанавливать режим игры
	//(если где нибудь несанкционировано было изменение режима) 
	void SetRM() { this->lastrm = rm; }
	//полностью меняет режим 
	void ChangeRunMode(RUNMODE RM) { lastrm = rm; this->rm = RM; }

};