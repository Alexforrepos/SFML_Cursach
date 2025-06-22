#pragma once
#include "GameClasses/Plant.h"
#include "Utils/Config.h"
class Apex : public Plant {
    
public:
    Apex() = default;
    Apex(uint8_t line, uint8_t col);
    void update() override;
    void sendMsg(const std::shared_ptr<Engine::MSG>& msg) override;

   /* template <class Archive>
    void serialize(Archive& ar)
    {
        ar(cereal::base_class<Plant>(this));
        
    }*/
}; 

