#pragma once
#include "O_Manager.h"
#include "ResourceManager.h"
#include "Button.h"

class Menu
{
	std::vector<Button*> buttons;
	sf::Music& Ost;
	bool isstarted;
	Menu()
		:isstarted(false), Ost(*Res_Manager::get().get_access<sf::Music*>("Casey_Edwards_feat_Victor_Borba_-_Bury_The_Light_b64f0d584.mp3"))
	{

	}
public:
	friend void START();

	void Start();
	void Run();
	void Close();

	bool IsStarted() { return isstarted; }


	static Menu& get()
	{
		static Menu m;
		return m;
	}

};