#pragma once
#include <vector>
#include "Button.h"	

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

};