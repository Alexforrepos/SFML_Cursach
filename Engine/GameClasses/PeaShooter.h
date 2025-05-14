        //std::cout << "dadadad";
        //TODO::перенеси общие части в родительский класс PLant пример MSG_TYPE из  MSG (VI KA)
        //TODO::если репитер это скорострел то нужно чтобы он наследовался от peashooter он не отличается ничем кроме выпуска пулек епта (VI KA)
        //TODO::исправь свой трабл с сериализацией 
        //TODO::также нахрена ты в конструктор уже известного типа ты передаешь его тип 
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
        ar(shootTimer);  // если нужен таймер
    }
};
