#pragma once
#include <SFML/Graphics.hpp>
#include "MSG_Manager.h"
#include <algorithm>
#include "Object.h"

class O_Manager {
    std::vector<std::shared_ptr<Object>> ObjVector;
    MSG_Manager& msgm;

    O_Manager() : msgm(MSG_Manager::get()) {}

public:
    static O_Manager& get() {
        static O_Manager inst;
        return inst;
    }

    void clear() {
        ObjVector.clear();
        std::cout << " ___________________________________________ " << std::endl;
    }

    void addObject(std::shared_ptr<Object> obj);
    void update();
    void draw(sf::RenderWindow& win);
};