#include "Menu.h"
#include "Game.h"
#include "Host.h"
#include "Client.h"
#include "ResourceManager.h"  
#include "MSG_Manager.h"
#include "MSG.h"
#include "O_Manager.h"
#include "Config_load.h"

void START()
{
	Game::Get().ChangeRunMode(Game::RUNMODE::RUNMODE_GAME);
	Menu::get().Ost.stop();
}

void NET_HOST()
{
	Host::Get().Start(53000);
}

void NER_CLIENT()
{
	Client::Get().Start("125.0.0.0", 53000);
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
		NER_CLIENT
	));

	for (auto b : buttons)
		MSG_Manager::get().Recieve(new MSG(MSG_TYPE_CREATE(b, nullptr)));
}

void Menu::Run()
{
	/// тут ошибка ты в функции старта уже добавил в очередь обработки все кнопки
	/* for (auto b : buttons)
	 {
		 b->Update();
	 }*/
}

void Menu::Close()
{
	O_Manager::get().clear();
}
