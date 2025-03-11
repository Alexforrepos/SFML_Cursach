#pragma once
#include <SFML/Network.hpp>

class I_Pacatable
{


public:
	/// <summary>
	/// метод кладет в пакет данные пакуемого объекта
	/// </summary>
	/// <param name="packet"> куда кладет </param>
	/// <returns>значение для конвеера(тот же пакет)</returns>
	virtual sf::Packet& pack(sf::Packet& packet) = 0;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="packet">откуда данные берутся</param>
	/// <returns>чистые данные и размер</returns>
	virtual	std::pair<void*,size_t> open(sf::Packet& packet) = 0;

};

