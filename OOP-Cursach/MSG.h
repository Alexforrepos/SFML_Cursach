#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <variant>

class Object;
class O_Manager;

enum class MSG_TYPE
{
	MSG_TYPE_MOVE, MSG_TYPE_KILL, MSG_TYPE_CREATE,MSG_TYPE_DEAL_DAMAGE
};

struct MSG_TYPE_MOVE
{
	sf::Vector2f dir;
	Object* obj;

	MSG_TYPE_MOVE(sf::Vector2f dir, Object* obj)
		: dir(dir), obj(obj)
	{
	}

	MSG_TYPE_MOVE()
	{
		dir = { 0,0 };
		obj = nullptr;
	}


	void reverse()
	{
		dir.x *= -1;
		dir.y *= -1;
	}


	bool operator==(const MSG_TYPE_MOVE& other) const
	{
		return false;
	}
};

struct MSG_TYPE_KILL
{
	Object* victim = nullptr,*killer= nullptr;

	MSG_TYPE_KILL() = default;

	MSG_TYPE_KILL(Object* victim, Object* killer)
		: victim(victim), killer(killer)
	{
	}

	

	bool operator==(const MSG_TYPE_KILL& other) const
	{
		return victim == other.victim;
	}
};

struct MSG_TYPE_CREATE
{
	Object* creature = nullptr, * creator = nullptr;

	bool operator==(const MSG_TYPE_CREATE& other) const
	{
		return creature == other.creature && creator == other.creator;
	}
};

struct MSG_TYPE_DEAL_DAMAGE
{
	Object* target, *killer;
	short damage;
};

class MSG	
{
public:
	std::variant<MSG_TYPE_MOVE, MSG_TYPE_KILL, MSG_TYPE_CREATE,MSG_TYPE_DEAL_DAMAGE> MSG_TYPE = MSG_TYPE_MOVE();
	friend class O_Manager;

	MSG() = default;
	MSG(const std::variant<MSG_TYPE_MOVE, MSG_TYPE_KILL, MSG_TYPE_CREATE, MSG_TYPE_DEAL_DAMAGE>& MSG_TYPE): MSG_TYPE(MSG_TYPE) {};

	operator MSG_TYPE_MOVE&() { return std::get<MSG_TYPE_MOVE>(this->MSG_TYPE); }
	operator MSG_TYPE_KILL&() { return std::get<MSG_TYPE_KILL>(this->MSG_TYPE); }
	operator MSG_TYPE_CREATE&() { return std::get<MSG_TYPE_CREATE>(this->MSG_TYPE); }
	operator MSG_TYPE_DEAL_DAMAGE&() { return std::get<MSG_TYPE_DEAL_DAMAGE>(this->MSG_TYPE); }


};