        //std::cout << "dadadad";
   
#pragma once
#include "GameClasses/Plant.h"

class PeaShooter : public Plant
{
protected:
    Timer shootTimer;
public:
    PeaShooter() = default;
    PeaShooter(uint8_t line, uint8_t col);
    void update() override;
    void sendMsg(const std::shared_ptr<Engine::MSG>& msg) override;

};
