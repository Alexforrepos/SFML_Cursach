#include "Game.h"
#include "Menu.h"

Game* Game::game = nullptr;

void Game::Run()
{
	sf::Event ev;
	while (win.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			win.clear();
			this->Close();
			return;
		default:
			break;
		}
	}
	
	static Menu menu;
	switch (int(rm))
	{
		case int(RUNMODE::RUNMODE_MENU) :
			if (!menu.IsStarted())
				menu.Start();
			break;
			case int(RUNMODE::RUNMODE_GAME) :
				if (rm != lastrm && rm == RUNMODE::RUNMODE_GAME)
				{
					OMg.clear();
					std::cout << " GameMode Inits\n";
					SetRM();
				}
			break;
	default:
		break;
	}

	OMg.update();
	OMg.draw(win);
	win.display();
	win.clear();

}



Game::Game(std::string res_filename)
	:win(sf::VideoMode::VideoMode(sf::VideoMode::getDesktopMode()), "Plants vs Zombies", sf::Style::Fullscreen),
	OMg(*O_Manager::getmger()),
	MsMg(*MSG_Manager::getmger()),
	RMg(*Res_Manager::getmger()), rm(RUNMODE::RUNMODE_MENU),isRun(true)
{
	if (Res_Manager::getmger()->load_from_file(res_filename))
		throw "Res load err";
}

