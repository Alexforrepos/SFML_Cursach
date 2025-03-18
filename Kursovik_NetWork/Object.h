#pragma once
#include "MSG.h"
#include "I_Pos.h"
#include "I_Type.h"
#include "I_Identifiable.h"
#include <SFML/Graphics.hpp>

class Object
	: public I_Pos , public I_Type , public I_Identifiable
{
	//���������� ���������� �� id
	unsigned long long id;
	//���������� ���������� �� ���������
	int type_; 
public:

	Object(int type) 
		: id(I_Identifiable::getId()),type_(type)
	{

	}
	/// <summary>
	/// ����� ���������� �� ���������� ������ �������
	/// </summary>
	virtual void update() = 0;
	/// <summary>
	/// ����� ���������� �� ��������� �������
	/// </summary>
	/// <param name="win">���� � ������� ������ ����������</param>
	virtual void draw(sf::RenderWindow& win) = 0;
	/// <summary>
	/// ����� ���������� �� ������� ������� �� ���������
	/// </summary>
	/// <param name="msg">��������� �� ������� ��������� ������</param>
	virtual void sendMsg(MSG* msg) = 0;

	// ������������ ����� I_Identifiable

	//����� ��� ��������� ID
	unsigned long long getId() override { return id; };

	//����� ��� ����������� ���� �������
	int type() { return type_; }
};

