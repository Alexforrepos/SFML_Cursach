        //std::cout << "dadadad";
        //TODO::�������� ����� ����� � ������������ ����� PLant ������ MSG_TYPE ��  MSG (VI KA)
        //TODO::���� ������� ��� ���������� �� ����� ����� �� ������������ �� peashooter �� �� ���������� ����� ����� ������� ����� ���� (VI KA)
        //TODO::������� ���� ����� � ������������� 
        //TODO::����� ������� �� � ����������� ��� ���������� ���� �� ��������� ��� ��� 
#pragma once
#include "GameClasses/Plant.h"

class PeaShooter : public Plant
{
protected:
    Timer shootTimer;
public:
    PeaShooter() = default;
    PeaShooter(const std::string& plantType, uint8_t line, uint8_t col);
    void update() override;
    void sendMsg(const std::shared_ptr<Engine::MSG>& msg) override;

    template <class Archive>
    void serialize(Archive& ar) 
    {
        ar(cereal::base_class<Plant>(this));
        ar(shootTimer);  // ���� ����� ������
    }
};
