#pragma once
#include "I_Object.h"
class Effect :
    public I_Object
{
    sf::Clock effecttime; // ��� ������������ ������� �������
    int durity_asmill; // ������������ ������� � ������������
public:
    
    sf::Clock& time() { return effecttime; }
    void restart() { effecttime.restart(); }
};