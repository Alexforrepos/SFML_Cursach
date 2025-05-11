// Skorostrel.h
#pragma once
#include "GameClasses/PeaShooter.h"

class Skorostrel : public PeaShooter {
public:
    Skorostrel() = default; // для сериализации

    // конструктор, который вы наверняка зовёте при «посадке»
    Skorostrel(const std::string& plantType, uint8_t line, uint8_t col);

    // остальное наследуется от PeaShooter (update, draw, getPos и т.д.)

    template <class Archive>
    void serialize(Archive& ar) {
        // сериализуем ВСЁ, что делает PeaShooter + Plant
        ar(cereal::base_class<PeaShooter>(this));
        // никаких своих полей нет
    }
};
