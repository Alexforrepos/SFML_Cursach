#pragma once
#include "Interfaces/I_Serialize.h"
#include <SFML/Graphics.hpp>
#include <iostream>

//класс предназначенный для счета периодического времени
class Timer
	: public I_Serialize
{
	sf::Clock timer;
	int time_d;

public:
	//возвращает прошло ли времени больше чем кд
    bool operator()(void) const {  // Добавлен const
        return timer.getElapsedTime().asMilliseconds() >= time_d;
    }


	Timer(int time_d = 0)
		: timer(), time_d(time_d)
	{
	}
	//заставляет считать заново таймер
	void restart() { timer.restart(); }

    int getRemainingTime() const {
        int elapsed = timer.getElapsedTime().asMilliseconds();
        return (time_d > elapsed) ? (time_d - elapsed) : 0;
    }

    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::base_class<I_Serialize>(this));

        // Сериализуем время cooldown'а
        ar(time_d);

        if constexpr (Archive::is_loading::value) {
            // При загрузке сбрасываем таймер
            timer.restart();

            // Можно добавить дополнительную логику инициализации
            // Например, проверку на валидность time_d
            if (time_d < 0) {
                time_d = 0; // Или другое значение по умолчанию
                std::cerr << "Warning: Loaded negative time_d, reset to 0\n";
            }
        }
    }
};

