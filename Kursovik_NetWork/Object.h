#pragma once
#include "MSG.h"
#include "I_Pos.h"
#include "I_Type.h"
#include "I_Identifiable.h"
#include <SFML/Graphics.hpp>

class Object
	: public I_Pos , public I_Type , public I_Identifiable
{
	//переменная отвечающая за id
	unsigned long long id;
	//переменная отвечающая за типизацию
	int type_; 
public:

	Object(int type) 
		: id(I_Identifiable::getId()),type_(type)
	{

	}
	/// <summary>
	/// метод отвечающий за внутреннюю логику объекта
	/// </summary>
	virtual void update() = 0;
	/// <summary>
	/// метод отвечающий за отрисовку объекта
	/// </summary>
	/// <param name="win">окно в котором объект отрисуется</param>
	virtual void draw(sf::RenderWindow& win) = 0;
	/// <summary>
	/// метод отвечающий за реакцию объекта на сообщение
	/// </summary>
	/// <param name="msg">сообщение на которое реагирует объект</param>
	virtual void sendMsg(MSG* msg) = 0;

	// Унаследовано через I_Identifiable

	//метод для получения ID
	unsigned long long getId() override { return id; };

	//метод для определения типа объекта
	int type() { return type_; }
};

