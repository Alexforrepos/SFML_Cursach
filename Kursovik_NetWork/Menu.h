#pragma once
#include <vector>
#include "Button.h"	
#include "Timer.h"

class Menu
{
	bool isrun;
public:
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