#pragma once
#include "I_Object.h"
#include "MSG_Manager.h"	


class Primer
	: public I_Object
{
	// Унаследовано через I_Object
	void Update() override;
	void SendMSG(MSG* msg) override;
	void Draw(sf::RenderWindow& win) override;
};

