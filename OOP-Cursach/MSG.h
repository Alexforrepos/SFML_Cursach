#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <variant>

class I_Object;

enum class MSG_TYPE
{
	MSG_TYPE_MOVE, MSG_TYPE_KILL, MSG_TYPE_CREATE
};

struct MSG_TYPE_MOVE
{
	sf::Vector2f dir;
	I_Object* obj;

	MSG_TYPE_MOVE(const sf::Vector2f& dir, I_Object* obj)
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
	I_Object* victim = nullptr,*killer= nullptr;

	MSG_TYPE_KILL() = default;

	MSG_TYPE_KILL(I_Object* victim, I_Object* killer)
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
	I_Object* creature = nullptr, * creator = nullptr;

	bool operator==(const MSG_TYPE_CREATE& other) const
	{
		return creature == other.creature && creator == other.creator;
	}
};

struct MSG
{
	std::variant<MSG_TYPE_MOVE, MSG_TYPE_KILL, MSG_TYPE_CREATE> MSG_TYPE = MSG_TYPE_MOVE();

	MSG() = default;
	
	MSG(const std::variant<MSG_TYPE_MOVE, MSG_TYPE_KILL, MSG_TYPE_CREATE>& MSG_TYPE)
		: MSG_TYPE(MSG_TYPE)
	{
	}

};