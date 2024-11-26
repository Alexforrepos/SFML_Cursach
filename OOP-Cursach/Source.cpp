#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "O_Manager.h"
#include "ResourceManager.h"
#include "DEBUG_CLASS.h"
using namespace std;
using namespace sf;

int main()
{
	RenderWindow win(VideoMode::VideoMode(VideoMode::getDesktopMode()), "Plants vs Zombies",Style::Fullscreen);
	auto om = O_Manager::getmger();
	DEBUG_CLASS d;
	om->add_obj(&d);
	auto rm = ResourceManager::getmger();
	Event ev;
	auto mm = MSG_Manager::get_mger();
	mm->add(new MSG(MSG_TYPE_KILL(&d, &d)));
	mm->add(new MSG(MSG_TYPE_KILL(&d, &d)));
	
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

		om->update(); om->draw(win);
		win.display();
	}
	O_Manager::deinit();
}