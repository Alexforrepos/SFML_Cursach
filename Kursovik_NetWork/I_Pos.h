#pragma once
#include <SFML/Graphics.hpp>

class I_Pos
{
	
public:
	/// <summary>
	/// метод для определения позиции 
	/// </summary>
	/// <returns> sf::Vector<float>(x,y позиция) которое показывает точку позиции </returns>
	virtual sf::Vector2f getPos() = 0;
	
	/// <summary>
	/// метод который "двигает" объект
	/// </summary>
	/// <param name="other">вектор(x,y позиция) добавляемый к позиции</param>
	virtual void changePos(sf::Vector2f other) = 0;

	/// <summary>
	/// метод который меняет позицию на другую
	/// </summary>
	/// <param name="other">вектор(x,y позиция) на который меняется текущий</param>
	virtual void setPos(sf::Vector2f other) = 0;
};

