#pragma once
#include "Interfaces/I_Pos.h"
#include "Interfaces/I_Type.h"
#include "Interfaces/I_Identifiable.h"
#include "Interfaces/I_Serialize.h"
#include "Utils/SpriteWrapper.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "MSG.h"
#include <iostream>
#include <mutex>

//std::mutex logmutex;

static void logMessage(std::string msg)
{

	std::cout << msg << std::endl;
//	logmutex.unlock();
}


class Object
	: public I_Pos,
	public I_Type,
	public I_Identifiable,
	//public I_Serialize

	public std::enable_shared_from_this<Object>
{
protected:
	unsigned long long id;
	int type_;

public:
	Object()
		: type_(int(Types::None)), id(I_Identifiable::generateID())
	{
	};

	Object(int type)
		: id(I_Identifiable::getId()),
		type_(type) {
	}

	template<typename T>
	Object(std::shared_ptr<T> ptr) : id(ptr->getId()), type_(ptr->type()) {}

	virtual ~Object() = default;

	
	virtual void update() {};
	virtual void draw(sf::RenderWindow& win) {};
	virtual void sendMsg(const std::shared_ptr<Engine::MSG>& msg) {};

	
	unsigned long long getId() override { return id; }
	int type() override { return type_; }

	
	template <class Archive>
	void serialize(Archive& ar)
	{
		ar(cereal::base_class<I_Serialize>(this));
		ar(id, type_);
	}

	// Унаследовано через I_Pos
	sf::Vector2f getPos() override;
	void changePos(const sf::Vector2f& other) override;
	void setPos(sf::Vector2f other) override;
};