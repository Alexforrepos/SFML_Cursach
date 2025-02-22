#pragma once
#include "O_Manager.h"
#include "ResourceManager.h"
#include "Button.h"


//Класс преднсзначенный для инициализации и хранения меню-объетов
class Menu
{
	
	sf::Music& Ost;
	bool isstarted;
	Menu()
		:isstarted(false), Ost(Res_Manager::get().get_access<sf::Music>("Casey_Edwards_feat_Victor_Borba_-_Bury_The_Light_b64f0d584.mp3"))
	{

	}
public:
	//функция кнопки запуска игры 
	friend void START();
	//инициализация кнопок и другого
	void Start();
	//Выполнения действий выполняемых каждый игровой цикл
	void Run();
	//освобождение ресурсов без удаления класса
	void Close();
	//флаг возврат
	bool IsStarted() { return isstarted; }
	//инициализациия 
	static Menu& get()
	{
		static Menu m;
		return m;
	}

};