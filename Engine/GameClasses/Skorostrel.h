// Skorostrel.h
#pragma once
#include "GameClasses/PeaShooter.h"

class Skorostrel : public PeaShooter {
public:
    Skorostrel() = default; // ��� ������������

    // �����������, ������� �� ��������� ����� ��� ��������
    Skorostrel(uint8_t line, uint8_t col);

    // ��������� ����������� �� PeaShooter (update, draw, getPos � �.�.)

    //template <class Archive>
    //void serialize(Archive& ar) {
    //    // ����������� �Ѩ, ��� ������ PeaShooter + Plant
    //    ar(cereal::base_class<PeaShooter>(this));
    //    // ������� ����� ����� ���
    //}
};
