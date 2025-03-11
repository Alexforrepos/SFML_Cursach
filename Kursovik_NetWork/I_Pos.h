#pragma once
#include <SFML/Graphics.hpp>

class I_Pos
{
	
public:
	/// <summary>
	/// ����� ��� ����������� ������� 
	/// </summary>
	/// <returns> sf::Vector<float>(x,y �������) ������� ���������� ����� ������� </returns>
	virtual sf::Vector2f getPos() = 0;
	
	/// <summary>
	/// ����� ������� "�������" ������
	/// </summary>
	/// <param name="other">������(x,y �������) ����������� � �������</param>
	virtual void changePos(sf::Vector2f other) = 0;

	/// <summary>
	/// ����� ������� ������ ������� �� ������
	/// </summary>
	/// <param name="other">������(x,y �������) �� ������� �������� �������</param>
	virtual void setPos(sf::Vector2f other) = 0;
};

