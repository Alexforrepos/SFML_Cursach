#pragma once
#include "I_Object.h"
#include "MSG_Manager.h"
#include "ResourceManager.h"

class FOREVER_VIRGIN
	:public Object
{
public:

	FOREVER_VIRGIN();

	// ������������ ����� I_Object
	sf::Sprite spr;

	sf::Clock timeofdying;
	// ������������ ����� Object
	void Update() override;

	void SendMSG(MSG* msg) override;

	void Draw(sf::RenderWindow& win) override;

};

