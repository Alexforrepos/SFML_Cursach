#pragma once
#include <vector>
#include "./../../Engine/R_Manager.h"
#include "./../Utils/Timer.h"
#include "./../GameClasses/Button.h"	

class Menu
{
public:
	enum class State
	{
		Base = 1,
		Multiplayer,
		Settings
	};
private:
	sf::RectangleShape BackGround;

	State state;
	bool change;

	bool isrun;

	Menu()
		: state(State::Base), isrun(false), change(false),
		BackGround({0,0})
	{
		
	}

public:
	friend void SETTINGS();
	friend void BACK_TO_MAIN();
	friend void MULT();

	static void ChangeMode(const State& newState);

	static Menu& get()
	{
		static Menu inst;
		return inst;
	}

	void start();
	void run();
	void close();

	bool getIsRun() { return isrun; }
	State getCurrentState() { return state; }
};