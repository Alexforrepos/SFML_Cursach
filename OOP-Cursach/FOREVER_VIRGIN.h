#pragma once
#include "I_Object.h"
#include "MSG_Manager.h"
#include "ResourceManager.h"
#include "LOOSE_VIRGIN.h"
#include "O_Manager.h"

class FOREVER_VIRGIN
	:public Object
{
private:
	LOOSE_VIRGIN* NEVER;
	sf::Sprite spr;
public:

	FOREVER_VIRGIN();

	// Унаследовано через Object
	void Update() override;

	void SendMSG(MSG* msg) override;

	void Draw(sf::RenderWindow& win) override;

};

