#pragma once
#include "I_Object.h"
#include "MSG_Manager.h"
#include "ResourceManager.h"

class LOOSE_VIRGIN
	:public Object
{
public:
	LOOSE_VIRGIN();
	
	
	// Унаследовано через Object
	void Update() override;// отправка инфы
	void SendMSG(MSG* msg) override;// реакция на сообщение
	void Draw(sf::RenderWindow& win) override;

};

