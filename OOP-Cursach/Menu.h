#pragma once
#include "O_Manager.h"
#include "ResourceManager.h"
#include "Button.h"

class Menu
{
	std::vector<Button*> buttons;
public:
	void Start();
	void Run();
	void Close();

	Menu()
	{
	}
};