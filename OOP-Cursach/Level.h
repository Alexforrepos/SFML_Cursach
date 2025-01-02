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
		
	};
	void SendMSG(MSG* msg) 
	{
		switch (msg->MSG_TYPE.index())
		{
		case (int)MSG_TYPE::MSG_TYPE_KILL:
			if (MSG_TYPE_KILL(*msg).victim->Serialize() == (int)Serialize_Enum::Gologram && MSG_TYPE_KILL(*msg).victim == MSG_TYPE_KILL(*msg).killer)
				this->s.Plant(MSG_TYPE_KILL(*msg).victim);
			break;
		default:
			break;
		}
	}
	void Draw(sf::RenderWindow& win) override
	{
		this->s.Draw(win);
	}

	int Serialize() { return int(Serialize_Enum::Level); }

};
