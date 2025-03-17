#include "Menu.h"
#include "Game.h"

using namespace std;

void START()
{
	Game::get().setState(Game::State::GameProcess);
}

void Menu::start()
{
	std::vector<Button*> bvect;

	bvect.emplace_back(
		sf::Text("DANYA", (R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf")), 40),
		sf::Vector2f(1400, 150),
		sf::Vector2f(300, 100),
		START);
}

void Menu::run()
{
}

void Menu::close()
{
}
