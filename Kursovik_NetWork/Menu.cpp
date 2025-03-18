#include "Menu.h"
#include "Game.h"

using namespace std;

void START()
{
	Game::get().setState(Game::State::GameProcess);
}

void EXIT()
{
	Game::get().setState(Game::State::Prepare);
	Game::get().close();
	Game::get().setState(Game::State::None);
}

void Menu::start()
{
	std::vector<Button*> bvect;

	bvect.emplace_back(
		sf::Text("Start", (R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf")), 40),
		sf::Vector2f(1400, 150),
		sf::Vector2f(300, 100),
		START);
	bvect.emplace_back(
		sf::Text("Exit", (R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf")), 40),
		sf::Vector2f(1400, 150),
		sf::Vector2f(300, 300),
		EXIT
		);
}

void Menu::run()
{
}

void Menu::close()
{
}
