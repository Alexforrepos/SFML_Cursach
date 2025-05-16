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
		MSG_TYPE_KILL_BY_ID,
		MSG_TYPE_ADD_EFFECT ,
		MSG_TYPE_REMOVE_EFFECT ,
		MSG_TYPE_SET_INVINCIBILITY

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

	class MSG_TYPE_SET_INVINCIBILITY
		: public MSG
	{
	public:
		unsigned long long id;
		bool set;

		MSG_TYPE_SET_INVINCIBILITY(unsigned long long id, bool set)
			: MSG(int(MSG_TYPE::MSG_TYPE_SET_INVINCIBILITY)),
			id(id), set(set)
		{

		}
	};
	class MSG_TYPE_ADD_EFFECT 
		: public MSG 
	{
	public:
		std::shared_ptr<class Effect> effect;
		std::shared_ptr<Object> target;

		MSG_TYPE_ADD_EFFECT(std::shared_ptr<Effect> eff, std::shared_ptr<Object> tgt)
			: MSG(int(MSG_TYPE::MSG_TYPE_ADD_EFFECT))
			, effect(std::move(eff)), target(std::move(tgt))
		{

		}
	};

	class MSG_TYPE_REMOVE_EFFECT 
		: public MSG 
	{
	public:
		uint64_t targetId;
		uint32_t effectId;

		MSG_TYPE_REMOVE_EFFECT(uint64_t tgtId, uint32_t effId)
			: MSG(int(MSG_TYPE::MSG_TYPE_REMOVE_EFFECT))
			, targetId(tgtId), effectId(effId)
		{

		}
	};

	class MSG_NET_TYPE
		:public MSG
	{
		std::string byte;


	};
}


