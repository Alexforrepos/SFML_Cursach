#include "Game.h"
#include "Menu.h"
#include "Game_Proc.h"
#include "Client.h"
#include "Host.h"

Game* Game::game = nullptr;

void Game::Run()
{
	sf::Event ev;
	static Menu& menu = Menu::get();
	static Game_Proc& gprc = Game_Proc::get();

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


	switch (int(rm))
	{
		case int(RUNMODE::RUNMODE_MENU) :
			if (!menu.IsStarted() && rm == RUNMODE::RUNMODE_MENU && rm != lastrm)
			{
				menu.Start();
				SetRM();
			}
		menu.Run();
		break;
		case int(RUNMODE::RUNMODE_GAME) :
			if (rm != lastrm && rm == RUNMODE::RUNMODE_GAME && !gprc.GetIsRun())
			{
				OMg.clear();
				gprc.Start();
				SetRM();
			}
		gprc.Run();
		break;
		default:
			break;
	}

	OMg.update();
	if (Client::Get().IsConnected())
		Client::Get().BuffDraw(win);
	OMg.draw(win);
	win.display();
	if (Host::Get().IsStarted())
		Host::Get().SendWindow(win);
	win.clear();

}



Game::Game(std::string res_filename)
	:win(sf::VideoMode::VideoMode(sf::VideoMode::getDesktopMode()), "Plants vs Zombies"),
	OMg(*O_Manager::getmger()),
	MsMg(*MSG_Manager::getmger()),
	RMg(*Res_Manager::getmger()), rm(RUNMODE::RUNMODE_MENU), isRun(true), lastrm(RUNMODE::RUNMODE_GAME)
{
	auto rand_seed = time(NULL);
	srand(rand_seed);
	std::cout << "Rand_seed = " << rand_seed << std::endl;
	if (Res_Manager::getmger()->load_from_file(res_filename))
		throw "Res load err";

}

