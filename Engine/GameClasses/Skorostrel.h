#pragma once
#include "GameClasses/PeaShooter.h"
#include "GameClasses/Projectile.h"
class Skorostrel : public PeaShooter {
protected:
    Timer secondShotTimer;
    bool pendingSecondShot = false;
public:
    Skorostrel() = default; // ��� ������������

    // �����������, ������� �� ��������� ����� ��� ��������
    Skorostrel(uint8_t line, uint8_t col);

    void update() override;

//    template <class Archive>
//    void serialize(Archive& ar) {
//        ar(cereal::base_class<PeaShooter>(this));
//        ar(secondShotTimer, pendingSecondShot);
//    }
};