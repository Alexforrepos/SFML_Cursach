#pragma once
#include <vector>
#include "Button.h"	

class Menu
{
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

};