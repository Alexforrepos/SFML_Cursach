#pragma once
#include "MSG.h"
#include <vector>
#include <memory>

//
//пример добавления сообщения в обработку
//MSG_Manager::get().addMSG(new MSG_TYPE_MOVE({123,123},this))
//


class MSG_Manager {
private:
    std::vector<std::shared_ptr<MSG>> MSGVector;

    // Закрытый конструктор для реализации singleton паттерна
    MSG_Manager() = default;

public:
    // Синглтон метод для доступа к экземпляру MSG_Manager
    static MSG_Manager& get() {
        static MSG_Manager inst;
        return inst;
    }

    // Метод для добавления сообщения
    void addMSG(std::shared_ptr<MSG> msg)
    {
        MSGVector.emplace_back(std::move(msg)); 
    }

    // Метод для очистки вектора
    void clear()
    {
        MSGVector.clear();
    }

    // Метод для получения вектора сообщений
    std::vector<std::shared_ptr<MSG>>& getVector()
    {
        return MSGVector;
    }
};