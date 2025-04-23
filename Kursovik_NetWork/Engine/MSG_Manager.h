#pragma once
#include "MSG.h"
#include <vector>
#include <memory>

class MSG_Manager {
private:
    std::vector<std::shared_ptr<Engine::MSG>> MSGVector;
    MSG_Manager() = default;

public:

    static MSG_Manager& get() {
        static MSG_Manager inst;
        return inst;
    }

    void addMSG(std::shared_ptr<Engine::MSG> msg) {
        MSGVector.emplace_back(std::move(msg));
    }

    void clear() {
        MSGVector.clear();
    }

    std::vector<std::shared_ptr<Engine::MSG>>& getVector() {
        return MSGVector;
    }
};