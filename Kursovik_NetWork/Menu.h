#pragma once
#include <vector>
#include "Timer.h"
#include "NetClass.h"

class Menu
{
	bool isrun;
public:
	/// <summary>
	/// ������������� ���� ������	
	/// </summary>
	void start();
	/// <summary>
	/// ���� ����
	/// </summary>
	void run();
	/// <summary>
	/// ������� ���� �������� ����
	/// </summary>
	void close();

	bool getIsRun() { return isrun; }
};