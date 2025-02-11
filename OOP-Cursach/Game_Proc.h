#pragma once
#include "ResourceManager.h"

class Game_Proc
{
	friend class Game;

	sf::Music& Ost;
	bool isrun;
public:

	Game_Proc()
		:isrun(false),
		Ost(*Res_Manager::get().get_access<sf::Music*>("JoJo's_Bizarre_Adventure_TV2_OST_—_Stardust_Crusaders_www_lightaudio.mp3"))
	{
		Ost.setVolume(50);
		Ost.setLoop(true);
	}

	bool GetIsRun() { return isrun; };

	void Run();
	void Close();
	void Start();
};