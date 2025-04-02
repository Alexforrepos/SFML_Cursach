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


public:
	GameProcess()
		: isActive(false)
	{

	}
	
	/// <returns>возвращает состояние цикла</returns>
	bool isRun() { return isActive; }

	/// <summary>
	/// создание всех объектов игры 
	/// </summary>
	void start();


	/// <summary>
	/// внутренний цикл игры
	/// </summary>
	void run();


	/// <summary>
	/// закрытие игрового процесса 
	/// </summary>
	void close();

};