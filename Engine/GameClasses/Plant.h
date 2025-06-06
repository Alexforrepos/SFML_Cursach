﻿#pragma once
#include "Engine/Object.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "Engine/R_Manager.h"
#include "Utils/Timer.h"
#include "Utils/Config.h"
class Plant : public Object
{
	friend class Surface;

protected:
	sf::Sprite sprite;
	std::string plantType;
	std::string textureId;
	uint8_t line, col;
	uint16_t HP;
	bool isTakingDamage = true;

public:
	Plant() = default;


	Plant(const std::string& plantType,
		const std::string& textureId,
		uint8_t line,
		uint8_t col,
		uint16_t HP)
		: Object(int(Types::BasePlantType))
		, plantType(plantType)
		, textureId(textureId)
		, line(line)
		, col(col)
		, HP(HP)
	{

		sprite.setTexture(R_Manager::get().access<sf::Texture>(textureId));
	}

	virtual ~Plant() = default;


	void draw(sf::RenderWindow& win) override {
		win.draw(sprite);
	}

	sf::Vector2f getPos() override
	{
		return sprite.getPosition();
	}

	void changePos(const sf::Vector2f& other) override {
		setPos(getPos() + other);
	}

	void setPos(sf::Vector2f other) override {
		sprite.setPosition(other);
	}

	std::string getType() { return plantType; }

	template <class Archive>
	void serialize(Archive& ar) {
		ar(cereal::base_class<Object>(this),
			plantType,
			textureId,      // ← сериализуем
			line,
			col,
			HP);

		// сохраняем текущее состояние спрайта
		sf::Vector2f position = sprite.getPosition();
		sf::Vector2f scale = sprite.getScale();
		float        rotation = sprite.getRotation();
		sf::IntRect  textureRect = sprite.getTextureRect();
		sf::Color    color = sprite.getColor();

		ar(position, scale, rotation, textureRect, color, isTakingDamage);

		if constexpr (Archive::is_loading::value) {
			// при загрузке сначала назначаем текстуру
			sprite.setTexture(R_Manager::get().access<sf::Texture>(textureId));
			// а потом восстанавливаем остальные параметры
			sprite.setPosition(position);
			sprite.setScale(scale);
			sprite.setRotation(rotation);
			sprite.setTextureRect(textureRect);
			sprite.setColor(color);
		}
	}
};
