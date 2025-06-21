#pragma once
#include "GameClasses/PeaShooter.h"
#include "Utils/Config.h"
#include "Engine/MSG_Manager.h"
#include "Engine/R_Manager.h"
#include "Projectile.h"
class ThreeShooter : public PeaShooter {
public:
    ThreeShooter() = default; // для сериализации
    ThreeShooter(uint8_t line, uint8_t col);
    void update() override;

   /* template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::base_class<PeaShooter>(this));
    }*/
};