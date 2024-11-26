#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "O_Manager.h"
#include "ResourceManager.h"
using namespace std;
using namespace sf;

int main()
{
	RenderWindow win(VideoMode::VideoMode(VideoMode::getDesktopMode()), "Plants vs Zombies",Style::Fullscreen);
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
		win.display();
	}
	O_Manager::deinit();
}