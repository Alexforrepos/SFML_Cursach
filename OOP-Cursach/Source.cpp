#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "O_Manager.h"
#include "DEBUG_CLASS.h"
using namespace std;
using namespace sf;

int main()
{
	auto om = O_Manager::getmger();
	RenderWindow win(VideoMode::VideoMode(1200, 1200), "Tempale");
	Event ev;
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
		{
			om->add_obj(new DEBUG_CLASS());
		}
		om->update(); om->draw(win);
		win.display();
	}
	O_Manager::deinit();
}