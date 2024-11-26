#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "O_Manager.h"
#include "ResourceManager.h"
using namespace std;
using namespace sf;

int main()
{
	RenderWindow win(VideoMode::VideoMode(VideoMode::getDesktopMode()), "Plants vs Zombies",Style::Fullscreen);
	auto om = O_Manager::getmger();
	auto rm = ResourceManager::getmger();
	rm->load_from_file("./resources/res_list.txt");
	auto r = rm->get_access<sf::Texture*>("00_0.png");
	sf::RectangleShape rect({ 300, 300 });
	rect.setTexture(r);
	rect.setPosition(30, 30);
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
		win.draw(rect);
		om->update(); om->draw(win);
		win.display();
	}
	O_Manager::deinit();
}