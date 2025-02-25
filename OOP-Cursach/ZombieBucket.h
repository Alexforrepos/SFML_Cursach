#pragma once
#include "Zombie.h"

class ZombieBucket : public Zombie {
private:
    int armor; 
public:
    ZombieBucket();
    virtual void SendMSG(MSG* msg) override;
};