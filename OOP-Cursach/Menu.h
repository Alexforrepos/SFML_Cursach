#pragma once
#include "O_Manager.h"
#include "ResourceManager.h"
#include "Button.h"

class Menu
{
	std::vector<Button*> buttons;
	bool isstarted;
public:
	void Start();
	void Run();
	void Close();

	bool IsStarted() { return isstarted; }

	Menu()
		:isstarted(false)
	{

	}
};