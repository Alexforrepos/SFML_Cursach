#pragma once
#include "ResourceManager.h"


//класс преднаначенный для регулировки и инициализации конкретно игрового цикла
class Game_Proc
{
	friend class Game;

	sf::Music& Ost;
	bool isrun;

	unsigned Sun_value;
	Game_Proc()
		:isrun(false), Sun_value(0),
		Ost(Res_Manager::get().get_access<sf::Music>("JoJo's_Bizarre_Adventure_TV2_OST_—_Stardust_Crusaders_www_lightaudio.mp3"))
	{
		Ost.setVolume(50);
		Ost.setLoop(true);
	}
public:
	//Инициализация
	static Game_Proc& get()
	{
		static Game_Proc gp;
		return gp;
	}

	bool GetIsRun() { return isrun; };
	unsigned& GetSunValue() { return Sun_value; }
	//выполнение тех действий которые необходимо выполнять каждую итерацию игрового цикла
	void Run();
	//освобождение ресурсов без уничтожения класса
	void Close();
	//запуск и иницализация Game_Proc
	//внутри создание левела и если надо будет то карт и друих кнопок
	void Start();
};