#include "O_Manager.h"

void O_Manager::addObject(std::shared_ptr<Object<void>> obj) {
    ObjVector.push_back(std::move(obj));
}

void O_Manager::draw(sf::RenderWindow& win) {
    for (auto& obj : ObjVector)
        obj->draw(win);
}

void O_Manager::update() {
    std::vector<std::shared_ptr<Object<void>>> gulag;

    for (const auto& obj : ObjVector)
        obj->update();

    auto msgs = msgm.getVector();

    for (const auto& msg : msgs) {
        for (const auto& obj : ObjVector)
            obj->sendMsg(msg.get());

        switch (msg->getIndex()) {
        case MSG_TYPE::MSG_TYPE_KILL: {
            auto killMsg = static_cast<MSG_TYPE_KILL*>(msg.get());
            auto it = std::find_if(ObjVector.begin(), ObjVector.end(),
                [&killMsg](const auto& obj) { return obj.get() == killMsg->victim.get(); });
            if (it != ObjVector.end()) {
                gulag.push_back(*it);
            }
            break;
        }
        case MSG_TYPE::MSG_TYPE_CREATE: {
            auto createMsg = static_cast<MSG_TYPE_CREATE*>(msg.get());
            addObject(createMsg->creature);
            break;
        }
        }
    }

    for (const auto& obj : gulag) {
        auto it = std::find(ObjVector.begin(), ObjVector.end(), obj);
        if (it != ObjVector.end()) {
            ObjVector.erase(it);
        }
    }

    msgm.clear();
}