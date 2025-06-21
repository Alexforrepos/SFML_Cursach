#include "Skorostrel.h"

Skorostrel::Skorostrel(uint8_t line, uint8_t col)
    : PeaShooter(line, col)
    , secondShotTimer(100) // задержка между двумя выстрелами (например, 100 мс)
    , pendingSecondShot(false)
{
    plantType = "Skorostrel";
    textureId = "Skorostrel.png";
    sprite.setTexture(R_Manager::get().access<sf::Texture>(textureId));
    sprite.setScale(0.15f, 0.15f);
    sprite.setColor(sf::Color(255, 255, 255, 200));
    // основная перезарядка оставляем такой же, как у обычного PeaShooter
    shootTimer = Timer(1000);
    shootTimer.restart();
}

void Skorostrel::update() {
    // Если ещё не был сделан второй выстрел
    if (!pendingSecondShot) {
        // Ждём основной таймер
        if (shootTimer()) {
            // Первый выстрел
            auto& cfg = Config::getInstance();
            unsigned damage = cfg["PlantParams"]["Plants"]["PeaShooter"]["Damage"].get<unsigned>();
            unsigned velocity = 2;
            auto& tex = R_Manager::get().access<sf::Texture>("pea.png");
            auto pos = getPos();
            MSG_Manager::get().addMSG(
                std::make_shared<Engine::MSG_TYPE_CREATE>(
                    std::make_shared<Projectile>(velocity, line, damage, tex, pos),
                    (Object*)this
                )
            );
            // Готовимся ко второму выстрелу
            pendingSecondShot = true;
            secondShotTimer.restart();
            // Перезапускаем основной таймер, чтобы не быстрее обычного стрелять
            shootTimer.restart();
        }
    }
    else {
        // Ждём задержку перед вторым выстрелом
        if (secondShotTimer()) {
            // Второй выстрел
            auto& cfg = Config::getInstance();
            unsigned damage = cfg["PlantParams"]["Plants"]["PeaShooter"]["Damage"].get<unsigned>();
            unsigned velocity = 2;
            auto& tex = R_Manager::get().access<sf::Texture>("pea.png");
            auto pos = getPos();
            MSG_Manager::get().addMSG(
                std::make_shared<Engine::MSG_TYPE_CREATE>(
                    std::make_shared<Projectile>(velocity, line, damage, tex, pos),
                    (Object*)this
                )
            );
            // Сброс состояния
            pendingSecondShot = false;
        }
    }
}
