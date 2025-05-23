#include "ResourceManager.h"  
#include "Config_load.h"
#include "MSG_Manager.h"
#include "O_Manager.h"
#include "Client.h"
#include "Menu.h"
#include "Game.h"
#include "Host.h"
#include "MSG.h"

void START()
{
	Game::Get().ChangeRunMode(Game::RUNMODE::RUNMODE_GAME);
	Menu::get().isstarted = false;
	Menu::get().Ost.stop();
	Menu::get().Close();
}

void NET_HOST()
{
	
}

void NET_CLIENT()
{ 

}

void EXIT()
{
	Game::Get().Close();
}

void Menu::Start()
{
	std::vector<Button*> buttons;
	isstarted = true;
	O_Manager::get().clear();
	if (Config_load::getconfig().get().at("SoundOn").get<int>())
		Ost.play();
	Ost.setLoop(true);

	buttons.clear();
	buttons.push_back(new Button(
		sf::Text("DANYA", (Res_Manager::get().get_access<sf::Font>("PaluiSPDemo-Bold.otf")), 40),
		sf::Vector2f(1400, 150),
		sf::Vector2f(300, 100),
		START
	));
	buttons.push_back(new Button(
		sf::Text("Host", (Res_Manager::get().get_access<sf::Font>("PaluiSPDemo-Bold.otf")), 40),
		sf::Vector2f(700, 150),
		sf::Vector2f(1000, 400),
		NET_HOST
	));
	buttons.push_back(new Button(
		sf::Text("Client", (Res_Manager::get().get_access<sf::Font>("PaluiSPDemo-Bold.otf")), 40),
		sf::Vector2f(700, 150),
		sf::Vector2f(300, 400),
		NET_CLIENT
	));
	buttons.push_back(new Button(
		sf::Text("Exit", Res_Manager::get().get_access<sf::Font>("PaluiSPDemo-Bold.otf"), 40),
		sf::Vector2f(1400, 150),
		sf::Vector2f(300, 600),
		EXIT
	));

	for (auto b : buttons)
		MSG_Manager::get().Recieve(new MSG(MSG_TYPE_CREATE(b, nullptr)));
}

void Menu::Run()
{

}

void Menu::Close()
{
	this->isstarted = false;
}
