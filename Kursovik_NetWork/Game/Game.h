#pragma once
#include "./../Interfaces/I_Serialize.h"
#include "./GameManagers/GameProcess.h"
#include "./../Engine/R_Manager.h"
#include "./../Engine/O_Manager.h"
#include "./GameManagers/Menu.h"
#include <SFML/Graphics.hpp>


class Game :
	public I_Serialize
{
public:
	enum class State
		: uint8_t
	{
		None,
		Menu,
		NetWait,
		Prepare,
		GameProcess
	};

	struct
	{
		std::string profileName = "";

		int levelUnlok = 0;


	} GameData;

private:
	sf::RenderWindow win;
	O_Manager& omger;
	R_Manager& rmger;

	bool isrun;

	State state;


	Menu& menu;
	GameProcess gameproc;


	Game()
		: omger(O_Manager::get()),
		rmger(R_Manager::get()),
		win(sf::VideoMode(1000, 1000), "PVZ", sf::Style::Fullscreen), state(State::Prepare),
		isrun(true), menu(Menu::get())
	{
		//TODO::�������� �� ����� ����������� ������ ����
		rmger.pushFromFile("./Res/ResDistr.txt");
		menu.start();
		setState(State::Menu);
	}

public:
	static Game& get()
	{
		static Game inst;
		return inst;
	}

	/// <summary>
	/// �������� ������� ���� �� ������� ����
	/// </summary>
	void run();

	//�������� �������� �� ����
	bool getRun() { return isrun; }
	//�������� ����
	void close() { isrun = false; }

	/// <returns>��������� ����</returns>
	State& getState() { return state; }

	/// <param name="state">����� ��������� ����</param>
	void setState(State state) { this->state = state; }

	void menuClose()
	{
		menu.close();
	}

	// ������������ ����� I_Serialize

	std::vector<char> serialize() override;

	std::pair<Types, std::pair<void*, int>> deserialize(std::vector<char> data, size_t& readpoint) override;

};

