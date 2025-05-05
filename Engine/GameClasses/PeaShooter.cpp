#include "PeaShooter.h"


PeaShooter::PeaShooter(const std::string& plantType, uint8_t line, uint8_t col)
    : Plant(line, col, Config::getInstance()["PlantParams"]["Plants"]["PeaShooter"]["HP"]),
    plantType(plantType), shootTimer(300/*Config::getInstance()["PlantParams"]["Plants"]["PeaShooter"]["CD"]*/)
{
    
    std::cout << ".675757";
    shootTimer.restart();
}

void PeaShooter::update() 
{
    std::cout << ".144444444444444";
    if (shootTimer()) {
        // 1. ������ �� ������� ��������� ����
        auto& cfg = Config::getInstance();
        unsigned damage = cfg["PlantParams"]["Plants"]["PeaShooter"]["Damage"].get<unsigned>();
        unsigned velocity = 5; // ���� ���� �� �������, ���� �����

        // 2. ������ shared_ptr �� Projectile
        //    �����������: Projectile(uint16_t velocity, uint16_t line, uint16_t damage, sf::Texture& texture)
        auto& tex = R_Manager::get().access<sf::Texture>("pea.jpg");
        auto proj = std::make_shared<Projectile>(
            static_cast<uint16_t>(velocity),
            line,                     // ����� ���������� �������� �����, ���� ������� � � PeaShooter
            static_cast<uint16_t>(damage),
            tex
        );
        std::cout << "���� ����" << std::endl;
        // 3. ������������� ��������� ������� ������� � ����� PeaShooter
        proj->setPos(this->getPos());

        // 4. ������ ��������� � �������� ������ �������
        MSG_Manager::get().addMSG(
            std::make_shared<Engine::MSG_TYPE_CREATE>(proj, nullptr)
        );

        // 5. ���������� ������, ����� ��������� ������� �������� ����� 520 ��
        shootTimer.restart();
    }
    else
         ;
}

void PeaShooter::sendMsg(Engine::MSG* msg)
{

}

void PeaShooter::draw(sf::RenderWindow& win) {
    win.draw(sprite);
}

sf::Vector2f PeaShooter::getPos() {
    return sprite.getPosition();
}

void PeaShooter::changePos(const sf::Vector2f& other) {
    setPos(getPos() + other);
}

void PeaShooter::setPos(sf::Vector2f other) {
    sprite.setPosition(other);
}


CEREAL_REGISTER_TYPE(PeaShooter);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Plant, PeaShooter);
