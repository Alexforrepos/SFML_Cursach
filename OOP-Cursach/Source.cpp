#include <SFML/Graphics.hpp>
#include "O_Manager.h"
#include "ResourceManager.h"
#include "Primer.h"
using namespace std;
using namespace sf;

int main()
{
	system("chcp 1251 > 0");
	RenderWindow win(VideoMode::VideoMode(VideoMode::getDesktopMode()), "Plants vs Zombies",Style::Fullscreen);
	Event ev;
	auto p = O_Manager::getmger();
	Res_Manager::getmger()->load_from_file("./resources/res_list.txt");
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
		if (Keyboard::isKeyPressed(Keyboard::W))
			p->add_obj(new Primer());
		if (Keyboard::isKeyPressed(Keyboard::E))
			p->clear();
		p->update();
		p->draw(win);
		win.display();
	}
}