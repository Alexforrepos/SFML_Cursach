#pragma once
#include <SFML/Network.hpp>

class I_Pacatable
{


public:
	/// <summary>
	/// ����� ������ � ����� ������ ��������� �������
	/// </summary>
	/// <param name="packet"> ���� ������ </param>
	/// <returns>�������� ��� ��������(��� �� �����)</returns>
	virtual sf::Packet& pack(sf::Packet& packet) = 0;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="packet">������ ������ �������</param>
	/// <returns>������ ������ � ������</returns>
	virtual	std::pair<void*,size_t> open(sf::Packet& packet) = 0;

};

