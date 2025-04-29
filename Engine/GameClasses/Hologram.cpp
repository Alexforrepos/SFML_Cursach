#include "Hologram.h"


Hologram::Hologram(const sf::Vector2f& startPos, const std::string& type)
    : Object(static_cast<int>(Types::Hologram))
    , plantType(type)
    , Clicktime(200)
    , position(startPos)
{
    Clicktime.restart();
    sprite.setTexture(R_Manager::get().access<sf::Texture>("ps.png"));
    sprite.setColor(sf::Color(255, 255, 255, 150)); // ��������������
    sprite.setScale(0.3f, 0.3f);              // ���������������
    sprite.setOrigin(
        sprite.getLocalBounds().width / 2,
        sprite.getLocalBounds().height / 2);
}

void Hologram::update()
{
    // ���������� ���������� �� ��������
    sf::Vector2i mousePixel = sf::Mouse::getPosition();
    position = sf::Vector2f(static_cast<float>(mousePixel.x), static_cast<float>(mousePixel.y));
    sprite.setPosition(position);

    // ��� ������� ������ ������ � ��������� �������� � "�������" ����������
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && Clicktime())
    {
        // ������ ��������������� ������ shared_from_this:
        MSG_Manager::get().addMSG(
            std::make_shared<Engine::MSG_TYPE_KILL>(
                this, // victim � ��� ����������
                nullptr    // killer �� ���������
            )
        );
        Clicktime.restart();
    }
}

void Hologram::sendMsg(Engine::MSG* msg)
{

}

void Hologram::draw(sf::RenderWindow& win)
{
    std::cout << "x=" << position.x << "\n y=" << position.y << std::endl;
    win.draw(sprite);
}

sf::Vector2f Hologram::getPos()
{
    return position;
}

void Hologram::changePos(const sf::Vector2f& other)
{

}

void Hologram::setPos(sf::Vector2f other)
{

}



CEREAL_REGISTER_TYPE(Hologram);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Object, Hologram);