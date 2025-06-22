#include "ThreeShooter.h"

ThreeShooter::ThreeShooter(uint8_t line, uint8_t col)
    : PeaShooter(line, col)
{
    plantType = "ThreeShooter";
    textureId = "ThreeShooter.png";
    sprite.setTexture(R_Manager::get().access<sf::Texture>(textureId));
    sprite.setScale(0.1, 0.1);
    sprite.setColor(sf::Color(255, 255, 255, 200));
    shootTimer = Timer(1000);
    shootTimer.restart();
}

void ThreeShooter::update() {
    if (!shootTimer())
        return;

    auto& cfg = Config::getInstance();
    unsigned damage = cfg["PlantParams"]["Plants"]["PeaShooter"]["Damage"].get<unsigned>();
    unsigned velocity = 2;
    auto& tex = R_Manager::get().access<sf::Texture>("pea.png");
    auto currentPos = getPos();

    unsigned currentLevelIndex = cfg["GameData"]["levelUnlock"].get<unsigned>();
    auto& levels = cfg["Level"]["Levels"];
    if (!levels.is_array() || currentLevelIndex >= levels.size()) {
        return;
    }
    auto& levelCfg = levels[currentLevelIndex];
    unsigned totalLines = levelCfg["Line_Q"].get<unsigned>();

    for (int d = -1; d <= 1; ++d) {
        int8_t targetLine = static_cast<int8_t>(line) + d;
        if (targetLine < 0 || targetLine >= static_cast<int8_t>(totalLines))
            continue; 

        sf::Vector2f pos = currentPos;
        pos.y += d * sprite.getGlobalBounds().height;

        auto projectile = std::make_shared<Projectile>(
            static_cast<uint16_t>(velocity),
            static_cast<uint16_t>(targetLine),
            static_cast<uint16_t>(damage),
            tex,
            pos
        );
        MSG_Manager::get().addMSG(
            std::make_shared<Engine::MSG_TYPE_CREATE>(projectile, (Object*)this)
        );
    }

    shootTimer.restart();
}