#include "Menu.h"
#include "./../Game.h"

using namespace std;

// Функции-обработчики кнопок

#pragma region BUTTONS_CALLBACK


void START()
{
	Game::get().setState(Game::State::GameProcess);
	Game::get().closeMenu();
}

void EXIT()
{
	Game::get().setState(Game::State::Prepare);
	Game::get().close();
	Game::get().setState(Game::State::None);
}

void MULT()
{
	Menu::get().state = Menu::State::Multiplayer;
	Menu::get().change = true;
}

void SETTINGS()
{
	Menu::get().state = Menu::State::Settings;
	Menu::get().change = true;
}

void BACK_TO_MAIN()
{
	Menu::get().state = Menu::State::Base;
	Menu::get().change = true;
	
}

void Menu::ChangeMode(const State& newState)
{
	Menu::get().state = newState;
	Menu::get().start(); 
}
#pragma endregion



void Menu::start() {
	isrun = false;

	std::vector<Button*> bvect;
	O_Manager::get().clear();

	// Базовое меню
	if (state == State::Base)
	{
		bvect.push_back(
			new Button(
				sf::Text("Start", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40),
				sf::Vector2f(1400, 150),
				sf::Vector2f(300, 100),
				START
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
				sf::Text("Settings", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40),
				{ 1400,150 },
				{ 300,500 },
				SETTINGS
			)
		);

		bvect.push_back(
			new Button(
				sf::Text("Exit", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40),
				sf::Vector2f(1400, 150),
				{ 300,700 },
				EXIT
			)
		);
	}
	// Меню мультиплеера
	else if (state == State::Multiplayer)
	{
		bvect.push_back(
			new Button(
				sf::Text("Back", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40),
				sf::Vector2f(1400, 150),
				{ 300,100 },
				BACK_TO_MAIN
			)
		);

		// Здесь можно добавить кнопки для мультиплеера
		// ...
	}
	// Меню настроек
	else if (state == State::Settings)
	{
		bvect.push_back(
			new Button(
				sf::Text("Back", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40),
				sf::Vector2f(1400, 150),
				{ 300,100 },
				BACK_TO_MAIN
			)
		);

		// Здесь можно добавить настройки
		// ...
	}

	for (auto obj : bvect)
		O_Manager::get().addObject(std::shared_ptr<Object>(obj));

	isrun = true;
}

void Menu::run()
{
	static Timer escapeDelay(500);
	BackGround.setTexture(&R_Manager::get().access<sf::Texture>
		("textur-gas-kvas-com-h9hz-p-tekstura-rasteniya-protiv-zombi-8.jpg"));
	BackGround.setSize(sf::Vector2f(Game::get().win.getSize()));

	if (change)	
	{
		change = false;
		ChangeMode(state);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escapeDelay())
	{
		escapeDelay.restart();
		if (state != State::Base)
		{
			ChangeMode(State::Base); // Возврат в главное меню по ESC
			return;
		}

		EXIT();
	}
	Game::get().win.draw(BackGround);
}


void Menu::close()
{
	cout << "Menu class closed" << endl;
	isrun = false;
}