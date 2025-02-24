#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <variant>

class Object;
class O_Manager;

enum class MSG_TYPE
{
	MSG_TYPE_MOVE, MSG_TYPE_KILL, MSG_TYPE_CREATE, MSG_TYPE_DEAL_DAMAGE, MSG_NET_TYPE_KILL_HOLO, MSG_NET_TYPE_IMG_SEND
};

struct MSG_NET_TYPE_IMG_SEND
{
	sf::Image img;

	MSG_NET_TYPE_IMG_SEND(const sf::Image& img)
		: img(img)
	{
	}
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

struct MSG_NET_TYPE_KILL_HOLO
{
	// from Serialize
	sf::Vector2f pos, size;
	int type;

	MSG_NET_TYPE_KILL_HOLO(const sf::Vector2f& pos, const sf::Vector2f& size, int type)
		: pos(pos), type(type)
	{
	}
};

struct MSG_TYPE_KILL
{
	Object* victim = nullptr, * killer = nullptr;

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

	MSG_TYPE_CREATE(Object* creature, Object* creator)
		: creature(creature), creator(creator)
	{
	}
};

struct MSG_TYPE_DEAL_DAMAGE
{
	Object* target, * killer;
	short damage;

	MSG_TYPE_DEAL_DAMAGE(Object* target, Object* killer, short damage)
		: target(target), killer(killer), damage(damage)
	{
	}
};

class MSG
{
public:
	std::variant<MSG_TYPE_MOVE, MSG_TYPE_KILL, MSG_TYPE_CREATE, MSG_TYPE_DEAL_DAMAGE, MSG_NET_TYPE_KILL_HOLO, MSG_NET_TYPE_IMG_SEND> MSG_TYPE = MSG_TYPE_MOVE();
	friend class O_Manager;

	MSG() = default;
	MSG(const std::variant<MSG_TYPE_MOVE, MSG_TYPE_KILL, MSG_TYPE_CREATE,
		MSG_TYPE_DEAL_DAMAGE, MSG_NET_TYPE_KILL_HOLO, MSG_NET_TYPE_IMG_SEND>& MSG_TYPE) : MSG_TYPE(MSG_TYPE) {
	};

	operator MSG_TYPE_MOVE& () { return std::get<MSG_TYPE_MOVE>(this->MSG_TYPE); }
	operator MSG_TYPE_KILL& () { return std::get<MSG_TYPE_KILL>(this->MSG_TYPE); }
	operator MSG_TYPE_CREATE& () { return std::get<MSG_TYPE_CREATE>(this->MSG_TYPE); }
	operator MSG_TYPE_DEAL_DAMAGE& () { return std::get<MSG_TYPE_DEAL_DAMAGE>(this->MSG_TYPE); }
	operator MSG_NET_TYPE_KILL_HOLO& () { return std::get<MSG_NET_TYPE_KILL_HOLO>(this->MSG_TYPE); }
	operator MSG_NET_TYPE_IMG_SEND& () { return std::get<MSG_NET_TYPE_IMG_SEND>(this->MSG_TYPE); }

};

