#pragma once
#include "Interfaces/I_Serialize.h"
#include <SFML/Graphics.hpp>
#include <iostream>

//����� ��������������� ��� ����� �������������� �������
class Timer
	: public I_Serialize
{
	sf::Clock timer;
	int time_d;

public:
	//���������� ������ �� ������� ������ ��� ��
    bool operator()(void) const {  // �������� const
        return timer.getElapsedTime().asMilliseconds() >= time_d;
    }


	Timer(int time_d = 0)
		: timer(), time_d(time_d)
	{
	}
	//���������� ������� ������ ������
	void restart() { timer.restart(); }

    int getRemainingTime() const {
        int elapsed = timer.getElapsedTime().asMilliseconds();
        return (time_d > elapsed) ? (time_d - elapsed) : 0;
    }

    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::base_class<I_Serialize>(this));

        // ����������� ����� cooldown'�
        ar(time_d);

        if constexpr (Archive::is_loading::value) {
            // ��� �������� ���������� ������
            timer.restart();

            // ����� �������� �������������� ������ �������������
            // ��������, �������� �� ���������� time_d
            if (time_d < 0) {
                time_d = 0; // ��� ������ �������� �� ���������
                std::cerr << "Warning: Loaded negative time_d, reset to 0\n";
            }
        }
    }
};

