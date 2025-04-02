#pragma once
#include <vector>
#include "./../Utils/Timer.h"
#include "./../GameClasses/Button.h"	

class Menu
{
public:
	enum class State
	{
		Base = 1, Multplayer, Settings
	};
private:

	class Basic_Menu
	{
		bool isRun;
		friend Menu;

		void start()
		{

		}

	};


	State state;

	bool isrun;





	Menu()
		:state(State::Base), isrun(false)
	{

	}

	

public:

	static void ChangeMode();

	static Menu& get()
	{
		static Menu inst;
		return inst;
	}

	/// <summary>
	/// ������������� ���� ������	
	/// </summary>
	void start();
	/// <summary>
	/// ���� ����
	/// </summary>
	void run();
	/// <summary>
	/// ������� ���� �������� ����
	/// </summary>
	void close();

	bool getIsRun() { return isrun; }
};