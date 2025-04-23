#include "./../GameClasses/Skorostrel.h"
#include "./../Game.h"
#include "Card.h"

sf::Vector2f Card::basePosition = { 50.f, 50.f };
int Card::cardCounter = 0;


Card::Card(const std::string& plantType)
	:Object(int(Types::Cart)),
	clickTimer(2000),
	plantType(plantType)
{
	if ((basePosition.y + cardCounter * 120.f) > 1000) {
		cardCounter = 0;
	}

	sf::Vector2f position = basePosition + sf::Vector2f(0.f, cardCounter * 120.f);
	cardCounter++;


	sprite.setTexture(R_Manager::get().access<sf::Texture>("ps.png"));
	sprite.setPosition(position);
	sprite.setScale(0.2f, 0.2f);
	sprite.setColor(sf::Color(255, 255, 255, 200));
}

void Card::update() {
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(Game::get().getWindow());
	
	//sprite.setTexture(R_Manager::get().access<sf::Texture>("shkibidiSanya.png"));
	std::shared_ptr<Object> gologram(new Hologram(basePosition, plantType));

	if (sprite.getGlobalBounds().contains(sf::Vector2f(mousePixelPos))) {
		sprite.setColor(sf::Color::White);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickTimer())
		{
			MSG_Manager::get().addMSG(std::shared_ptr<Engine::MSG>(new Engine::MSG_TYPE_CREATE(gologram, std::make_shared<Object>(0))));
			clickTimer.restart();

			//MSG_Manager::get().addMSG(std::make_shared<MSG_TYPE_CREATE>(gologram, this));
		}
	}
	else 
	{
		sprite.setColor(sf::Color(255, 255, 255, 200));
	}


	/*
	if (currentHologram)
	{
		  currentHologram->update();
	}
	*/
}

void Card::draw(sf::RenderWindow& win)
{
	win.draw(sprite);
}

sf::Vector2f Card::getPos()
{
	return sprite.getPosition();
}

void Card::changePos(const sf::Vector2f& other)
{
	setPos(getPos() + other);
}

void Card::setPos(sf::Vector2f other)
{
	sprite.setPosition(other);
}

void Card::sendMsg(Engine::MSG* msg)
{

}


CEREAL_REGISTER_TYPE(Card);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Object, Card);
