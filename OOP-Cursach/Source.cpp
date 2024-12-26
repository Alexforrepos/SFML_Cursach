#include <SFML/Graphics.hpp>
#include "O_Manager.h"
#include "ResourceManager.h"
#include "Primer.h"
#include "FOREVER_VIRGIN.h"
using namespace std;
using namespace sf;

int main()
{
	system("chcp 1251 > 0");
	RenderWindow win(VideoMode::VideoMode(VideoMode::getDesktopMode()), "Plants vs Zombies",Style::Fullscreen);
	Event ev;
	auto p = O_Manager::getmger();
	Res_Manager::getmger()->load_from_file("./resources/res_list.txt");
	p->add_obj(new FOREVER_VIRGIN);
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
		
		p->update();
		p->draw(win);
		win.display();
	}
	O_Manager::deinit();
}