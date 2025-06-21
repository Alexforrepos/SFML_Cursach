#pragma once
#include "GameClasses/PeaShooter.h"
#include "GameClasses/Projectile.h"
class Skorostrel : public PeaShooter {
protected:
    Timer secondShotTimer;
    bool pendingSecondShot = false;
public:
    Skorostrel() = default; // для сериализации

    // конструктор, который вы наверняка зовёте при «посадке»
    Skorostrel(uint8_t line, uint8_t col);

    void update() override;

//    template <class Archive>
//    void serialize(Archive& ar) {
//        ar(cereal::base_class<PeaShooter>(this));
//        ar(secondShotTimer, pendingSecondShot);
//    }
};