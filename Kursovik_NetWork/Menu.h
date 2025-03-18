#pragma once
#include <vector>
#include "Button.h"	
#include "Timer.h"

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