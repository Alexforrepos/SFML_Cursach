#include "Object.h"
//CEREAL_REGISTER_TYPE(Object);
//CEREAL_REGISTER_POLYMORPHIC_RELATION(I_Serialize, Object);


sf::Vector2f Object::getPos()
{
	throw "Object virt exepts";
	return sf::Vector2f();
}

void Object::changePos(const sf::Vector2f& other)
{
	throw "Object virt exepts";
}

void Object::setPos(sf::Vector2f other)
{
	throw "Object virt exepts";
}
