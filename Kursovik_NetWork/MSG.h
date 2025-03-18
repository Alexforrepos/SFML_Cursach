#pragma once
#include "I_Pacatable.h"
#include <iostream>

class Object;

enum class MSG_TYPE
	: uint8_t
{
	MSG_TYPE_MOVE = 1, MSG_TYPE_KILL, MSG_TYPE_CREATE, MSG_TYPE_DAMAGE
};

class MSG :
	public I_Pacatable
{
protected:
	//����������� ���������� � ���������� ���� ����� �� ���� ����� �� ������� ��������� ��� ������
	MSG(int index)
		: index(MSG_TYPE(index))
	{

	}
	MSG_TYPE index;
public:
	MSG_TYPE getIndex() { return index; }

	virtual ~MSG() = default;

};


//c�������� � ��������
class MSG_TYPE_MOVE
	: public MSG
{
public:

	sf::Vector2f dir;
	unsigned long long id;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="dir">������ �������� �������</param>
	/// <param name="target">������ ������� ��������</param>
	MSG_TYPE_MOVE(sf::Vector2f dir, unsigned long long id)
		: MSG(int(MSG_TYPE::MSG_TYPE_MOVE)), id(id)
	{
	};
	~MSG_TYPE_MOVE() = default;



	// ������������ ����� MSG
	sf::Packet& pack(sf::Packet& packet) override;

	std::pair<void*, size_t> open(sf::Packet& packet) override;

};

//��������� �� ��������
class MSG_TYPE_KILL
	: public MSG
{
public:

	unsigned long long victim, killer;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="victim">������� ������� �������</param>
	/// <param name="killer">������� ������� �������</param>
	MSG_TYPE_KILL(unsigned long long& victim, unsigned long long& killer)
		: MSG(int(MSG_TYPE::MSG_TYPE_KILL)), victim(victim), killer(killer)
	{

	}



	// ������������ ����� MSG
	sf::Packet& pack(sf::Packet& packet) override;

	std::pair<void*, size_t> open(sf::Packet& packet) override;

};

//��������� �� ��������
class MSG_TYPE_CREATE
	:public MSG
{
public:
	unsigned long long creator;
	Object* creature;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="creature">�� ��� ��� �������</param>
	/// <param name="creator">��� ��� ������</param>
	MSG_TYPE_CREATE(Object* creature, unsigned long long creator) :
		MSG(int(MSG_TYPE::MSG_TYPE_CREATE)), creature(creature), creator(creator)
	{

	}


	// ������������ ����� MSG

	sf::Packet& pack(sf::Packet& packet) override;

	std::pair<void*, size_t> open(sf::Packet& packet) override;

};

//��������� � ��������� �����
class MSG_TYPE_DAMAGE
	: public MSG
{
public:
	unsigned damage;
	unsigned long long target, damager;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="damage">������ ������(������ �������������)</param>
	/// <param name="target">���� ������</param>
	/// <param name="damager">��� ��� ������� ����</param>
	MSG_TYPE_DAMAGE(unsigned damage, unsigned long long target, unsigned long long damager)
		:MSG(int(MSG_TYPE::MSG_TYPE_DAMAGE)), damage(damage), target(target), damager(damager)
	{
	}

	// ������������ ����� MSG
	sf::Packet& pack(sf::Packet& packet) override;
	std::pair<void*, size_t> open(sf::Packet& packet) override;
};