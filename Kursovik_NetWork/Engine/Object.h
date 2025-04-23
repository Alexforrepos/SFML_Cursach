#pragma once
#include "./../Interfaces/I_Pos.h"
#include "./../Interfaces/I_Type.h"
#include "./../Interfaces/I_Identifiable.h"
#include "./../Interfaces/I_Serialize.h"
#include "./../Game/Utils/SpriteWrapper.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "MSG.h"



class Object
	: public I_Pos,
	public I_Type,
	public I_Identifiable,
	public I_Serialize,
	std::enable_shared_from_this<Object>
{
protected:
	unsigned long long id;
	int type_;

public:
	Object() = default;

	Object(int type)
		: id(I_Identifiable::getId()),
		type_(type) {
	}

	template<typename T>
	Object(std::shared_ptr<T> ptr) : id(ptr->getId()), type_(ptr->type()) {}

	virtual ~Object() = default;

	// Чисто виртуальные методы
	virtual void update() {};
	virtual void draw(sf::RenderWindow& win) {};
	virtual void sendMsg(Engine::MSG* msg) {};

	// Реализация интерфейсов
	unsigned long long getId() override { return id; }
	int type() override { return type_; }

	// Сериализация через CRTP
	template <class Archive>
	void serialize(Archive& ar)
	{
		ar& cereal::base_class<I_Serialize>(this);
		ar& id & type_;
	}

	// Унаследовано через I_Pos
	sf::Vector2f getPos() override;
	void changePos(const sf::Vector2f& other) override;
	void setPos(sf::Vector2f other) override;
};