// Skorostrel.cpp
#include "Skorostrel.h"

Skorostrel::Skorostrel(uint8_t line, uint8_t col)
    : PeaShooter(
        line,
        col
    )
{
    this->plantType = "Skorostrel";
    // 1) ����������� textureId (���������� ���� Plant) �� ����
    this->textureId = "Skorostrel.png";

    // 2) ������������� �������� �������
    sprite.setTexture(R_Manager::get().access<sf::Texture>(textureId));

    // 3) ����� ��� ������� ���������� �������/����, ���� �����
    sprite.setScale(0.15, 0.15);
    sprite.setColor(sf::Color(255, 255, 255, 200));

    // 4) ������� � PeaShooter �� ��������� 300 ��, �� �� ������ ���������� ���,
    //    ��������, �������:
    shootTimer = Timer(250);  // ��� shootTimer, ���� �� ��� ��� �������
    shootTimer.restart();
}
