// Skorostrel.cpp
#include "Skorostrel.h"

Skorostrel::Skorostrel(const std::string& plantType, uint8_t line, uint8_t col)
// �������� PeaShooter::PeaShooter, ����� ������������ ��� ������ ��������
    : PeaShooter(
        plantType,
        line,
        col
    )
{
    // 1) ����������� textureId (���������� ���� Plant) �� ����
    this->textureId = "shkibidiSanya.png";

    // 2) ������������� �������� �������
    sprite.setTexture(R_Manager::get().access<sf::Texture>(textureId));

    // 3) ����� ��� ������� ���������� �������/����, ���� �����
    sprite.setScale(2.f, 2.f);
    sprite.setColor(sf::Color(255, 255, 255, 200));

    // 4) ������� � PeaShooter �� ��������� 300 ��, �� �� ������ ���������� ���,
    //    ��������, �������:
    shootTimer = Timer(150);  // ��� shootTimer, ���� �� ��� ��� �������
    shootTimer.restart();
}
