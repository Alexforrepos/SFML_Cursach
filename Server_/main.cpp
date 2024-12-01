#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main()
{
	RenderWindow win(VideoMode::VideoMode(600, 600), "Tempale");
	Event ev;
	while (win.isOpen())
	{
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
	
	}
}