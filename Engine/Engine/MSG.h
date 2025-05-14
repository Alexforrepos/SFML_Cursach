#pragma once
#include "./../Interfaces/I_Serialize.h"
#include <memory>
#include <iostream>
#include <vector>
#include <SFML/Network.hpp>

class Object;

namespace Engine
{
	enum class MSG_TYPE : uint8_t
	{
		MSG_NONE, MSG_TYPE_MOVE = 1,
		MSG_TYPE_KILL,
		MSG_TYPE_CREATE,
		MSG_TYPE_DAMAGE,
		MSG_NET_TYPE,
		MSG_TYPE_KILL_BY_ID

	};
	class MSG
		:public I_Serialize
	{
	protected:


		MSG(int index) : index(MSG_TYPE(index)) {}
		MSG_TYPE index;

	public:
		MSG()
			:index(MSG_TYPE::MSG_NONE) {
		};
		virtual ~MSG() = default;
		MSG_TYPE getIndex() const { return index; }
	};

	class MSG_TYPE_MOVE :
		public Engine::MSG {
	public:
		sf::Vector2f dir;
		std::shared_ptr<Object> target;  // Используем shared_ptr и шаблонный Object

		MSG_TYPE_MOVE(sf::Vector2f dir, std::shared_ptr<Object> target)
			: MSG(int(MSG_TYPE::MSG_TYPE_MOVE)), target(std::move(target)), dir(dir) {
		}
	};

	class MSG_TYPE_KILL : public MSG
	{
	public:
		Object* victim, * killer;

		MSG_TYPE_KILL(Object* victim, Object* killer)
			: MSG(int(MSG_TYPE::MSG_TYPE_KILL)), victim(victim), killer(killer)
		{
		}

		~MSG_TYPE_KILL()
		{

		}
	};

	class MSG_TYPE_CREATE : public MSG {
	public:
		std::shared_ptr<Object> creature;
		std::shared_ptr<Object>& creator;

		MSG_TYPE_CREATE(std::shared_ptr<Object> creature, Object*)
			: MSG(int(MSG_TYPE::MSG_TYPE_CREATE)), creature(std::move(creature)), creator(creator)
		{
		}

	};

	class MSG_TYPE_DAMAGE : public MSG {
	public:
		unsigned damage;
		std::shared_ptr<Object> target, damager;

		MSG_TYPE_DAMAGE(unsigned damage, std::shared_ptr<Object> target,
			std::shared_ptr<Object> damager)
			: MSG(int(MSG_TYPE::MSG_TYPE_DAMAGE)), damage(damage),
			target(std::move(target)), damager(std::move(damager)) {
		}
	};

	class MSG_TYPE_KILL_BY_ID
		: public MSG
	{
	public:
		unsigned long long victim, killer;

		MSG_TYPE_KILL_BY_ID(unsigned long long& victim, unsigned long long killer)
			: MSG(int(MSG_TYPE::MSG_TYPE_KILL_BY_ID)),
			victim(victim), killer(killer)
		{

		}
	};

	class MSG_NET_TYPE
		:public MSG
	{
		std::string byte;


	};
}


