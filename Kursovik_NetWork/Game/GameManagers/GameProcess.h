#pragma once
#include "./../../Engine/O_Manager.h"
#include "./../GameClasses/Surface.h"
#include "./../Utils/Timer.h"



/// <summary>
/// ����� ������� ������������� �� ������� �������
/// </summary>
class GameProcess
{
	bool isActive;


public:
	GameProcess()
		: isActive(false)
	{

	}
	
	/// <returns>���������� ��������� �����</returns>
	bool isRun() { return isActive; }

	/// <summary>
	/// �������� ���� �������� ���� 
	/// </summary>
	void start();


	/// <summary>
	/// ���������� ���� ����
	/// </summary>
	void run();


	/// <summary>
	/// �������� �������� �������� 
	/// </summary>
	void close();

};