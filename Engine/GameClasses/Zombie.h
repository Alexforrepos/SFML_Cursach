#pragma once
#include "Engine/O_Manager.h"
#include "GameClasses/Effect.h"
#include "Utils/Config.h"
#include "Utils/Timer.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <algorithm>

class Zombie : public Object
{
    friend class Effect;
    sf::Vector2f pos;
    uint16_t HP;
    uint16_t velocity;
    uint16_t damage;
    uint16_t line;
    sf::Sprite spr;
    bool isAttack;
    std::shared_ptr<Object> attackTarget;
    std::vector<EffectPtr> effects;
    Timer time;

public:
    Zombie() = default;

    Zombie(const uint16_t& HP, const uint16_t& velocity, const uint16_t& damage, const uint16_t& line, std::string textureId)
        : Object(int(Types::BaseZombieType)), HP(HP), velocity(velocity), damage(damage), line(line), isAttack(false), attackTarget(nullptr)
    {
        spr.setTexture(R_Manager::get().access<sf::Texture>(textureId));
    }

    Zombie(const uint16_t& line)
        : Zombie(
            Config::getInstance()["ZombieParams"]["Zombies"]["Zombie"]["HP"],
            Config::getInstance()["ZombieParams"]["Zombies"]["Zombie"]["Speed"],
            Config::getInstance()["ZombieParams"]["Zombies"]["Zombie"]["Damage"],
            line,
            "bullet.png")
    {
        spr.setScale(0.1f, 0.1f);
    }

    uint16_t getLine()
    {
        return this->line;
    }

    void draw(sf::RenderWindow& win) override
    {
        win.draw(spr);
    }

    sf::Vector2f getPos() override
    {
        return pos;
    }

    void setPos(sf::Vector2f other) override
    {
        this->pos = other;
        spr.setPosition(other);
    }

    void changePos(const sf::Vector2f& pos) override
    {
        this->pos.x -= velocity;
        spr.setPosition(this->pos);
    }

    sf::FloatRect getBounds() const
    {
        return spr.getGlobalBounds();
    }

    void setAttackTarget(std::shared_ptr<Object> target)
    {
        attackTarget = target;
        isAttack = (target != nullptr);
    }

    void update() override
    {
        if (isAttack && attackTarget)
        {
            if (this->time())
            {
                MSG_Manager::get().addMSG(
                    std::make_shared<Engine::MSG_TYPE_DAMAGE>(
                        damage,
                        attackTarget,
                        std::shared_ptr<Object>(this, [](Object*) {})
                    )
                );
            }
        }
        if (time() && !isAttack)
        {
            changePos(pos);
        }
        for (auto effect = effects.begin(); effect != effects.end(); )
        {
            if ((*effect)->tick(*this))
            {
                effect++;
            }
            else
            {
                effect = effects.erase(effect);
            }
        }
    }

    void sendMsg(const std::shared_ptr<Engine::MSG>& msg) override
    {
        switch (msg->getIndex())
        {
        case Engine::MSG_TYPE::MSG_TYPE_MOVE:
        {
            auto moveMsg = std::static_pointer_cast<Engine::MSG_TYPE_MOVE>(msg);
            if (moveMsg->target.get() == this)
            {
                sf::Vector2f newPos = pos + moveMsg->dir;
                setPos(newPos);
            }
            break;
        }
        case Engine::MSG_TYPE::MSG_TYPE_DAMAGE:
        {
            auto damageMsg = std::static_pointer_cast<Engine::MSG_TYPE_DAMAGE>(msg);
            if (damageMsg->target.get() == this)
            {
                if (HP <= damageMsg->damage)
                {
                    MSG_Manager::get().addMSG(
                        std::make_shared<Engine::MSG_TYPE_KILL>(this, damageMsg->damager.get())
                    );
                    HP = 0;
                    attackTarget = nullptr;
                    isAttack = false;
                }
                else
                {
                    HP -= damageMsg->damage;
                }
            }
            break;
        }
        case Engine::MSG_TYPE::MSG_TYPE_KILL:
        {
            auto killMsg = std::static_pointer_cast<Engine::MSG_TYPE_KILL>(msg);
            if (killMsg->victim == this)
            {
                HP = 0;
                attackTarget = nullptr;
                isAttack = false;
            }
            break;
        }
        case Engine::MSG_TYPE::MSG_TYPE_ADD_EFFECT:
        {
            auto effectMsg = std::static_pointer_cast<Engine::MSG_TYPE_ADD_EFFECT>(msg);
            if (effectMsg->target.get() == this)
            {
                addEffect(effectMsg->effect);
            }
            break;
        }
        case Engine::MSG_TYPE::MSG_TYPE_REMOVE_EFFECT:
        {
            auto removeEffectMsg = std::static_pointer_cast<Engine::MSG_TYPE_REMOVE_EFFECT>(msg);
            if (removeEffectMsg->targetId == this->getId())
            {
                for (auto it = effects.begin(); it != effects.end(); )
                {
                    if ((*it)->getId() == removeEffectMsg->effectId)
                    {
                        it = effects.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
            break;
        }
        default:
            break;
        }
    }

    void addEffect(const EffectPtr& eff)
    {
        effects.push_back(eff);
    }

    void removeEffect(const EffectPtr& eff = nullptr)
    {
        if (!eff)
        {
            effects.clear();
        }
        else
        {
            effects.erase(std::remove(effects.begin(), effects.end(), eff), effects.end());
        }
    }
};