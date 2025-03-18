#include "Menu.h"
#include "Game.h"
#include "Button.h"	
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

void Menu::start() {
    std::vector<Button*> bvect;

    // Используем push_back и явное создание объекта через new
    bvect.push_back(
        new Button(
            sf::Text("Start", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40),
            sf::Vector2f(1400, 150), // размер
            sf::Vector2f(300, 100),  // позиция
            START                     // функция
        )
    );

    bvect.push_back(
        new Button(
            sf::Text("Exit", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40),
            sf::Vector2f(1400, 150),
            sf::Vector2f(300, 300),
            EXIT
        )
    );

    for (auto obj : bvect)
        O_Manager::get().addObject(std::shared_ptr<Object>(obj));
}

void Menu::run()
{
	Timer escapeDelay(500);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escapeDelay())
	{
		escapeDelay.restart();
		EXIT();
	}
}

void Menu::close()
{
	cout << "Menu class closed" << endl;
}
