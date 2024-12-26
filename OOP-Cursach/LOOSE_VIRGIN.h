#pragma once
#include "I_Object.h"
#include "MSG_Manager.h"
#include "ResourceManager.h"

class LOOSE_VIRGIN
	:public Object
{
private:
	sf::Sprite spr;
public:
	LOOSE_VIRGIN(sf::Vector2f position);
	~LOOSE_VIRGIN()
	{

	}
	
	// ������������ ����� Object
	void Update() override;// �������� ����
	void SendMSG(MSG* msg) override;// ������� �� ���������
	void Draw(sf::RenderWindow& win) override;

};
