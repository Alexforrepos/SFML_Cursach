#include "Menu.h"
#include "./../Game.h"

using namespace std;



/// <summary>
/// функция кнопки старта уровня по напрямую на поле
/// </summary>
void START()
{
	Game::get().setState(Game::State::GameProcess);
	Game::get().menuClose();
}


///	кнопка выхода из меню - закрывает игру 
void EXIT()
{
	Game::get().setState(Game::State::Prepare);
	Game::get().close();
	Game::get().setState(Game::State::None);
	//cout << "exit click" << endl;
}

void MULT()
{

}

void Menu::start() {
	std::vector<Button*> bvect;
	O_Manager::get().clear();
	// Используем push_back и явное создание объекта через new
	bvect.push_back(
		new Button(
			sf::Text("Start", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40),
			sf::Vector2f(1400, 150), // размер
			sf::Vector2f(300, 100),  // позиция
			START                    // функция
		)
	);

	bvect.push_back(
		new Button(
			sf::Text("Multi", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40),
			{ 1400,150 },
			{ 300,300 },
			MULT
		)
	);



	bvect.push_back(
		new Button(
			sf::Text("Exit", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40),
			sf::Vector2f(1400, 150),
			{ 300,500 }, 
			EXIT
		)
	);

	for (auto obj : bvect)
		O_Manager::get().addObject(std::shared_ptr<Object>(obj));

	isrun = true;
}

void Menu::run()
{
	static Timer escapeDelay(500);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escapeDelay())
	{
		escapeDelay.restart();
		cout << "exit" << endl;
		EXIT();
	}
}

void Menu::close()
{
	cout << "Menu class closed" << endl;
	isrun = false;
}
