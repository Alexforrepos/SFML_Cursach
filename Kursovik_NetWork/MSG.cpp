#include "MSG.h"

sf::Packet& MSG_TYPE_MOVE::pack(sf::Packet& packet) {
    packet << static_cast<uint8_t>(getIndex()); // Упаковываем тип сообщения
    packet << dir.x << dir.y; // Упаковываем вектор направления
    return packet;
}


std::pair<void*, size_t> MSG_TYPE_MOVE::open(sf::Packet& packet) {
    sf::Vector2f unpackedDir;
    packet >> unpackedDir.x >> unpackedDir.y; // Распаковываем вектор направления
    dir = unpackedDir;
    return { nullptr, 0 };
}

sf::Packet& MSG_TYPE_KILL::pack(sf::Packet& packet) 
{
    packet << static_cast<uint8_t>(getIndex());
    // Упаковываем данные (если нужно)
    return packet;
}

std::pair<void*, size_t> MSG_TYPE_KILL::open(sf::Packet& packet) {
    // Распаковываем данные (если нужно)
    return { nullptr, 0 };
}

sf::Packet& MSG_TYPE_CREATE::pack(sf::Packet& packet) {
    packet << static_cast<uint8_t>(getIndex());
    // Упаковываем данные (если нужно)
    return packet;
}

std::pair<void*, size_t> MSG_TYPE_CREATE::open(sf::Packet& packet) {
    // Распаковываем данные (если нужно)
    return { nullptr, 0 };
}

sf::Packet& MSG_TYPE_DAMAGE::pack(sf::Packet& packet) {
    packet << static_cast<uint8_t>(getIndex());
    packet << damage; // Упаковываем урон
    return packet;
}

std::pair<void*, size_t> MSG_TYPE_DAMAGE::open(sf::Packet& packet) {
    packet >> damage; // Распаковываем урон
    return { nullptr, 0 };
}