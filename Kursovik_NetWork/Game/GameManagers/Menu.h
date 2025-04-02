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
	/// инициализация всех кнопок	
	/// </summary>
	void start();
	/// <summary>
	/// цикл меню
	/// </summary>
	void run();
	/// <summary>
	/// очистка всех объектов меню
	/// </summary>
	void close();

	bool getIsRun() { return isrun; }
};