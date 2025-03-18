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
	//конструктор специально в защищенном поле чтобы ни одна падла не создала сообщение без данных
	MSG(int index)
		: index(MSG_TYPE(index))
	{

	}
	MSG_TYPE index;
public:
	MSG_TYPE getIndex() { return index; }

	virtual ~MSG() = default;

};


//cообщение о движении
class MSG_TYPE_MOVE
	: public MSG
{
public:

	sf::Vector2f dir;
	unsigned long long id;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="dir">вектор движени€ объекта</param>
	/// <param name="target">объект который движетс€</param>
	MSG_TYPE_MOVE(sf::Vector2f dir, unsigned long long id)
		: MSG(int(MSG_TYPE::MSG_TYPE_MOVE)), id(id)
	{
	};
	~MSG_TYPE_MOVE() = default;



	// ”наследовано через MSG
	sf::Packet& pack(sf::Packet& packet) override;

	std::pair<void*, size_t> open(sf::Packet& packet) override;

};

//сообщение об убийстве
class MSG_TYPE_KILL
	: public MSG
{
public:

	unsigned long long victim, killer;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="victim">объекта который умирает</param>
	/// <param name="killer">объекта который убивает</param>
	MSG_TYPE_KILL(unsigned long long& victim, unsigned long long& killer)
		: MSG(int(MSG_TYPE::MSG_TYPE_KILL)), victim(victim), killer(killer)
	{

	}



	// ”наследовано через MSG
	sf::Packet& pack(sf::Packet& packet) override;

	std::pair<void*, size_t> open(sf::Packet& packet) override;

};

//сообщение об создании
class MSG_TYPE_CREATE
	:public MSG
{
public:
	unsigned long long creator;
	Object* creature;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="creature">то что уже создано</param>
	/// <param name="creator">тот кто создал</param>
	MSG_TYPE_CREATE(Object* creature, unsigned long long creator) :
		MSG(int(MSG_TYPE::MSG_TYPE_CREATE)), creature(creature), creator(creator)
	{

	}


	// ”наследовано через MSG

	sf::Packet& pack(sf::Packet& packet) override;

	std::pair<void*, size_t> open(sf::Packet& packet) override;

};

//сообщение о получении урона
class MSG_TYPE_DAMAGE
	: public MSG
{
public:
	unsigned damage;
	unsigned long long target, damager;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="damage">модуль дамага(только положительное)</param>
	/// <param name="target">цель дамага</param>
	/// <param name="damager">тот кто наносит урон</param>
	MSG_TYPE_DAMAGE(unsigned damage, unsigned long long target, unsigned long long damager)
		:MSG(int(MSG_TYPE::MSG_TYPE_DAMAGE)), damage(damage), target(target), damager(damager)
	{
	}

	// ”наследовано через MSG
	sf::Packet& pack(sf::Packet& packet) override;
	std::pair<void*, size_t> open(sf::Packet& packet) override;
};