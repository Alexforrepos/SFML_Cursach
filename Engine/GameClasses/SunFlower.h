#pragma once
#include "GameClasses/Plant.h"
#include "Utils/Timer.h"
#include "GameClasses/Sun.h"
#include "Engine/MSG_Manager.h"
#include "Engine/R_Manager.h"
#include "Utils/Config.h"
class SunFlower : public Plant {
    Timer sunTimer;

public:
    SunFlower() = default;
    SunFlower(uint8_t line, uint8_t col);

    void update() override;
    void sendMsg(const std::shared_ptr<Engine::MSG>& msg) override {}

    template<class Archive>
    void serialize(Archive& ar) {
        ar(cereal::base_class<Plant>(this), sunTimer);
    }
};
