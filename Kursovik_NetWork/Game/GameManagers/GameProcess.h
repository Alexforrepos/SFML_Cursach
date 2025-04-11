#pragma once
#include "./../../Engine/O_Manager.h"
#include "./../GameClasses/Surface.h"
#include "./../Utils/Timer.h"



/// <summary>
/// класс который ответственнен за игровой процесс
/// </summary>
class GameProcess
{
	bool isActive;

	uint16_t sun_q;
public:
	GameProcess()
		: isActive(false),sun_q(0)
	{
		Object* o;
		
	}

	static GameProcess& get()
	{
		static GameProcess inst;
		return inst;
	}
	
	/// <returns>возвращает состояние цикла</returns>
	bool isRun() { return isActive; }

	/// <summary>
	/// создание всех объектов игры 
	/// </summary>
	void start(int levelnumber);


	/// <summary>
	/// внутренний цикл игры
	/// </summary>
	void run();


	/// <summary>
	/// закрытие игрового процесса 
	/// </summary>
	void close();

	uint16_t getSun() { return sun_q; }

};