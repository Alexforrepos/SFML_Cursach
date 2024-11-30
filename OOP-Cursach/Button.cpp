#include "Button.h"
using namespace sf;
using namespace std;

void Button::Update()
{
	if (this->Intershape.getGlobalBounds().contains(static_cast<Vector2f>(Mouse::getPosition())))
	{
		if (Mouse::isButtonPressed(sf::Mouse::Left))
			f();

	}
}

void Button::SendMSG(MSG* msg)
{
}

void Button::Draw(sf::RenderWindow& win)
{
}
