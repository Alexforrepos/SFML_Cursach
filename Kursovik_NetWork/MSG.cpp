#include "MSG.h"

sf::Packet& MSG::MSG_TYPE_MOVE::pack(sf::Packet& packet)
{
    return packet;
}

std::pair<void*, size_t> MSG::MSG_TYPE_MOVE::open(sf::Packet& packet)
{
    return std::pair<void*, size_t>();
}

sf::Packet& MSG::MSG_TYPE_KILL::pack(sf::Packet& packet)
{
    return packet;
}

std::pair<void*, size_t> MSG::MSG_TYPE_KILL::open(sf::Packet& packet)
{
    return std::pair<void*, size_t>();
}

sf::Packet& MSG::MSG_TYPE_CREATE::pack(sf::Packet& packet)
{
    // TODO: вставьте здесь оператор return
    return packet;
}

std::pair<void*, size_t> MSG::MSG_TYPE_CREATE::open(sf::Packet& packet)
{
    return std::pair<void*, size_t>();
}

sf::Packet& MSG::MSG_TYPE_DAMAGE::pack(sf::Packet& packet)
{
    // TODO: вставьте здесь оператор return
    return packet;
}

std::pair<void*, size_t> MSG::MSG_TYPE_DAMAGE::open(sf::Packet& packet)
{
    return std::pair<void*, size_t>();
}
