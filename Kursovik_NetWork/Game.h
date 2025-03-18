#pragma once
#include "I_Serialize.h"
#include "O_Manager.h"
#include "R_Manager.h"
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
private:
	sf::RenderWindow win;
	O_Manager& omger;
	R_Manager& rmger;

	bool isrun;

	State state;


	Game()
		: omger(O_Manager::get()), rmger(R_Manager::get()), win(sf::VideoMode(1000, 1000), "PVZ"), state(State::Prepare), isrun(true)
	{
		//TODO::�������� �� ����� ����������� ������ ����
		rmger.pushFromFile("./Res/ResDistr.txt");

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

	/// <summary>
	/// 
	/// </summary>
	/// <returns>��������� ����</returns>
	State& getState() { return state; }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="state">����� ��������� ����</param>
	void setState(State state) { this->state = state; }

	// ������������ ����� I_Serialize

	std::vector<char> serialize() override;

	I_Serialize* deserialize(std::vector<char> data) override;

};

