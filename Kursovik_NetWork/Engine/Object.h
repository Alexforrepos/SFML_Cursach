#pragma once
#include "MSG.h"
#include "./../Interfaces/I_Pos.h"
#include "./../Interfaces/I_Type.h"
#include "./../Interfaces/I_Identifiable.h"
#include "./../Interfaces/I_Serialize.h"
#include <SFML/Graphics.hpp>
#include <memory>

template <typename Derived>
class Object : public I_Pos, public I_Type, public I_Identifiable, public I_Serialize<Derived> {
protected:
    unsigned long long id;
    int type_;

public:
    Object(int type) : id(I_Identifiable::getId()), type_(type) {}

    virtual ~Object() = default;

    // Чисто виртуальные методы
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& win) = 0;
    virtual void sendMsg(MSG* msg) = 0;

    // Реализация интерфейсов
    unsigned long long getId() override { return id; }
    int type() override { return type_; }

    // Сериализация через CRTP
    template <class Archive>
    void serialize(Archive& ar) {
        ar(id, type_);
    }
};