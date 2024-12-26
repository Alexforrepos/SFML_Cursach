#include "LOOSE_VIRGIN.h"



LOOSE_VIRGIN::LOOSE_VIRGIN()
{
	this->Position = { 500,500 };
	spr.setTexture(*Res_Manager::getmger()->get_access<sf::Texture*>("loose.jfif"));//������� ��������
	spr.setPosition(this->Position);//������� ��������
}

void LOOSE_VIRGIN::Update()
{		
	spr.setPosition(this->Position);//��������� ������� �������
}

void LOOSE_VIRGIN::SendMSG(MSG* msg)
{
	switch (msg->MSG_TYPE.index())
	{
	case (int)MSG_TYPE::MSG_TYPE_CREATE:
		std::cout << "F	" << MSG_TYPE_CREATE(*msg).creator << std::endl;
		break;
	case (int)MSG_TYPE::MSG_TYPE_MOVE:
		if (MSG_TYPE_MOVE(*msg).obj==this)//������� �� ���(�� ������� ����)
		{
			Position += MSG_TYPE_MOVE(*msg).dir;//������ ������������
			std::cout << "������ ���� ������" << std::endl;
		}
		break;
	default:
		break;
	}	
}

void LOOSE_VIRGIN::Draw(sf::RenderWindow& win)
{
	spr.setPosition(this->Position);
	win.draw(spr);//������������� �������
}


