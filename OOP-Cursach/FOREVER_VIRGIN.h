#pragma once
#include "I_Object.h"
#include "MSG_Manager.h"
#include "ResourceManager.h"
#include "LOOSE_VIRGIN.h"

class FOREVER_VIRGIN
	:public Object
{
private:
	LOOSE_VIRGIN* NEVER;
public:

	FOREVER_VIRGIN();

	// Унаследовано через Object
	void Update() override;

	void SendMSG(MSG* msg) override;

	void Draw(sf::RenderWindow& win) override;

};

