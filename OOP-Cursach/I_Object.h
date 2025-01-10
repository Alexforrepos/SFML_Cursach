#pragma once
#include <SFML/Graphics.hpp>
#include "MSG_Manager.h"

enum class Serialize_Enum{Object,Plant,Zombie,Hologram,Level,Pea,Effect};

class Object
{
protected:

	sf::Vector2f Position;

public:
	Object() = default;
	virtual void Update() = 0; // собственная логика
	virtual void SendMSG(MSG* msg) = 0; // получение сообщения
	virtual void Draw(sf::RenderWindow& win) = 0; // отрисовка

	virtual int Serialize() { return 0; } // получение типа объекиа

	sf::Vector2f getPos() const { return Position; }
	void SetPos(const sf::Vector2f& p) { Position = p; }
};