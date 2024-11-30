#include <SFML/Graphics.hpp>
#include "O_Manager.h"
#include "ResourceManager.h"
using namespace std;
using namespace sf;

int main()
{
	RenderWindow win(VideoMode::VideoMode(VideoMode::getDesktopMode()), "Plants vs Zombies",Style::Fullscreen);
	Event ev;
	ResourceManager::getmger()->load_from_file("./resources/res_list.txt");

	auto p = ResourceManager::getmger()->get_access<sf::Texture*>("00_0.png");
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
		win.display();
	}
}