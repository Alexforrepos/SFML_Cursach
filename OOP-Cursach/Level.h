#pragma once
#include "I_Object.h"
#include "Surface.h"
#include "EnemyManager.h"

template <int line_size,int line_count>
class Level :
	public Object
{
	EnemyManager e_m;
	Surface<line_size,line_count> s;

public:

	Level() 
		:e_m(),s()
	{

	}

	// Унаследовано через Object
	void Update() override
	{
		e_m.Update();
	};

	void SendMSG(MSG* msg) 
	{
		switch (msg->MSG_TYPE.index())
		{
		case (int)MSG_TYPE::MSG_TYPE_KILL:
			if (MSG_TYPE_KILL(*msg).victim->Serialize() == (int)Serialize_Enum::Hologram && MSG_TYPE_KILL(*msg).victim == MSG_TYPE_KILL(*msg).killer)
				this->s.Plant(MSG_TYPE_KILL(*msg).victim);
			if (MSG_TYPE_KILL(*msg).victim->Serialize() == (int)Serialize_Enum::Zombie)
				s.deactivateLines((Zombie*)MSG_TYPE_KILL(*msg).victim);
			if (MSG_TYPE_KILL(*msg).victim->Serialize() == int(Serialize_Enum::Plant))
				s.Wrest((Plant*)MSG_TYPE_KILL(*msg).victim);
			break;
		case (int)MSG_TYPE::MSG_TYPE_MOVE:
			if ((MSG_TYPE_MOVE(*msg).obj)->Serialize() == (int)Serialize_Enum::Zombie)
				this->s.CheckCollision((Zombie*)(MSG_TYPE_MOVE(*msg).obj));
			break;
		case (int)MSG_TYPE::MSG_NET_TYPE_KILL_HOLO:
			Hologram g(MSG_NET_TYPE_KILL_HOLO(*msg).pos, HoloType(MSG_NET_TYPE_KILL_HOLO(*msg).type));
			this->s.Plant(&g);
		}
	}
	void Draw(sf::RenderWindow& win) override
	{
		this->s.Draw(win);
	}
};