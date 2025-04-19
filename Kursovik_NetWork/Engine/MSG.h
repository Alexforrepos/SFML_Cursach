#pragma once
#include "./../Interfaces/I_Pacatable.h"
#include <memory>
#include <iostream>
#include <vector>
#include <SFML/Network.hpp>

template<typename Derived> class Object;
enum class MSG_TYPE : uint8_t {
    MSG_TYPE_MOVE = 1, MSG_TYPE_KILL, MSG_TYPE_CREATE, MSG_TYPE_DAMAGE,
    MSG_NET_ROOM_RECIEVE, MSG_NET_UPDATE_OBJECTS
};

class MSG 
{
protected:
    MSG(int index) : index(MSG_TYPE(index)) {}
    MSG_TYPE index;

    virtual sf::Packet& pack(sf::Packet& pack_) {
        pack_ << static_cast<int8_t>(index);
        return pack_;
    }

    virtual sf::Packet& open(sf::Packet& pack) {
        int8_t index_;
        pack >> index_;
        index = static_cast<MSG_TYPE>(index_);
        return pack;
    }

public:
    virtual ~MSG() = default;
    MSG_TYPE getIndex() const { return index; }
};

class MSG_TYPE_MOVE : public MSG {
public:
    sf::Vector2f dir;
    std::shared_ptr<Object<void>> target;  // Используем shared_ptr и шаблонный Object

    MSG_TYPE_MOVE(sf::Vector2f dir, std::shared_ptr<Object<void>> target)
        : MSG(int(MSG_TYPE::MSG_TYPE_MOVE)), target(std::move(target)), dir(dir) {
    }
};

class MSG_TYPE_KILL : public MSG {
public:
    std::shared_ptr<Object<void>> victim, killer;

    MSG_TYPE_KILL(std::shared_ptr<Object<void>> victim, std::shared_ptr<Object<void>> killer)
        : MSG(int(MSG_TYPE::MSG_TYPE_KILL)), victim(std::move(victim)), killer(std::move(killer)) {
    }
};

class MSG_TYPE_CREATE : public MSG {
public:
    std::shared_ptr<Object<void>> creature, creator;

    MSG_TYPE_CREATE(std::shared_ptr<Object<void>> creature, std::shared_ptr<Object<void>> creator)
        : MSG(int(MSG_TYPE::MSG_TYPE_CREATE)), creature(std::move(creature)), creator(std::move(creator)) {
    }
};

class MSG_TYPE_DAMAGE : public MSG {
public:
    unsigned damage;
    std::shared_ptr<Object<void>> target, damager;

    MSG_TYPE_DAMAGE(unsigned damage, std::shared_ptr<Object<void>> target,
        std::shared_ptr<Object<void>> damager)
        : MSG(int(MSG_TYPE::MSG_TYPE_DAMAGE)), damage(damage),
        target(std::move(target)), damager(std::move(damager)) {
    }
};

class MSG_NET_UPDATE_OBJECTS : public MSG {
protected:
    std::vector<std::shared_ptr<Object<void>>> objects;

public:
    MSG_NET_UPDATE_OBJECTS() : MSG(int(MSG_TYPE::MSG_NET_UPDATE_OBJECTS)) {}

    sf::Packet& pack(sf::Packet& pack_) override {
        MSG::pack(pack_);
        // Реализация упаковки объектов
        return pack_;
    }
};

class MSG_NET_ROOM_RECIEVE : public MSG {
    void* roomdata;
    size_t size;

public:
    MSG_NET_ROOM_RECIEVE() : 
        MSG(int(MSG_TYPE::MSG_NET_ROOM_RECIEVE)) {}
};