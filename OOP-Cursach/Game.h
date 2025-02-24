#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "O_Manager.h"
#include <string>



//�������� ����� ���� 
//������������ ��� ����������� ����������� ������ 
//��������� ��������� ����, ��������������� ����
//� ��.
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

#pragma region ����������
	//��������
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

	//��������� ������ �������� �� ����
	inline bool isRunning() { return isRun; }
	//�������� ���� ����
	void Run();

	//���������� ������� ��� ����
	inline int GetRunMod() { return int(rm); }
	//��������� ������������ ������������� ����� ����
	//(���� ��� ������ ����������������� ���� ��������� ������) 
	void SetRM() { this->lastrm = rm; }
	//��������� ������ ����� 
	void ChangeRunMode(RUNMODE RM) { lastrm = rm; this->rm = RM; }

};