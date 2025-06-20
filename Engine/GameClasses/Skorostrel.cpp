// Skorostrel.cpp
#include "Skorostrel.h"

Skorostrel::Skorostrel(uint8_t line, uint8_t col)
    : PeaShooter(
        line,
        col
    )
{
    this->plantType = "Skorostrel";
    // 1) Перекрываем textureId (защищённое поле Plant) на свою
    this->textureId = "Skorostrel.png";

    // 2) Перезагружаем текстуру спрайта
    sprite.setTexture(R_Manager::get().access<sf::Texture>(textureId));

    // 3) Можно при желании подправить масштаб/цвет, если нужно
    sprite.setScale(0.15, 0.15);
    sprite.setColor(sf::Color(255, 255, 255, 200));

    // 4) Таймаут у PeaShooter по умолчанию 300 мс, но вы можете подправить его,
    //    например, быстрее:
    shootTimer = Timer(250);  // или shootTimer, если вы его так назвали
    shootTimer.restart();
}
