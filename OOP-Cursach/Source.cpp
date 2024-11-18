#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
using namespace std;
using namespace sf;

int main()
{
	RenderWindow win(VideoMode::VideoMode(1200, 1200), "Tempale");
	Event ev;

	RectangleShape r(Vector2f(200, 200));
	r.setPosition(100, 100);
	r.setFillColor(sf::Color::Cyan);
	Texture t;
	t.loadFromFile("pmg.png");
	r.setTexture(&t, (200, 200));
	while (win.isOpen())
	{
		win.clear();
		while (win.pollEvent(ev))
		{
			switch (ev.type)
			{
			case Event::Closed:
				win.close();
				break;
			default:
				break;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
			r.move(Vector2f(1, 0));
		if (Keyboard::isKeyPressed(Keyboard::A))
			r.move(Vector2f(-1, 0));
		if (Keyboard::isKeyPressed(Keyboard::W))
			r.move(0, -1);
		if (Keyboard::isKeyPressed(Keyboard::S))
			r.move(0, 1);
		win.draw(r);
		win.display();
	}
}