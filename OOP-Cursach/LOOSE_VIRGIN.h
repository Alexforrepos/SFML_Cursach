#pragma once
#include "I_Object.h"
#include "MSG_Manager.h"
#include "ResourceManager.h"

class LOOSE_VIRGIN
	:public Object
{
public:
	LOOSE_VIRGIN();
	
	
	// ������������ ����� Object
	void Update() override;// �������� ����
	void SendMSG(MSG* msg) override;// ������� �� ���������
	void Draw(sf::RenderWindow& win) override;

};

