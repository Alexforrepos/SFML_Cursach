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
	
	/// <returns>���������� ��������� �����</returns>
	bool isRun() { return isActive; }

	/// <summary>
	/// �������� ���� �������� ���� 
	/// </summary>
	void start(int levelnumber);


	/// <summary>
	/// ���������� ���� ����
	/// </summary>
	void run();


	/// <summary>
	/// �������� �������� �������� 
	/// </summary>
	void close();

	uint16_t getSun() { return sun_q; }

};