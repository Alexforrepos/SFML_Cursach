#include "Menu.h"
#include "./../Game.h"

using namespace std;

// Button callbacks
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
	Menu::get().changeState(Menu::State::Multiplayer);
	
}

void SETTINGS()
{
	Menu::get().changeState(Menu::State::Settings);
}

void BACK_TO_MAIN()
{
	Menu::get().changeState(Menu::State::Base);
}

void Menu::changeState(const State& newState)
{
	m_state = newState;
	m_change = true;
}

void Menu::createBaseMenu()
{
	try {
		m_background.setTexture(&R_Manager::get().access<sf::Texture>(
			"textur-gas-kvas-com-h9hz-p-tekstura-rasteniya-protiv-zombi-8.jpg"));
	}
	catch (...) {
		m_change = false;
	}

	auto window = std::make_unique<InterfaceWindow>(sf::Vector2f(500, 950), sf::Vector2f(1400, 50));

	// Create buttons
	auto startBtn = std::make_unique<Button>(
		sf::Vector2f(400, 200), sf::Vector2f(),
		"Start", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40);
	startBtn->setCallback(START);

	auto multiBtn = std::make_unique<Button>(
		sf::Vector2f(400, 200), sf::Vector2f(),
		"Multi", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40);
	multiBtn->setCallback(MULT);

	auto settingsBtn = std::make_unique<Button>(
		sf::Vector2f(400, 200), sf::Vector2f(),
		"Settings", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40);
	settingsBtn->setCallback(SETTINGS);

	auto exitBtn = std::make_unique<Button>(
		sf::Vector2f(400, 200), sf::Vector2f(),
		"Exit", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40);
	exitBtn->setCallback(EXIT);

	// Add buttons to window
	window->addElement(std::move(startBtn));
	window->addElement(std::move(multiBtn));
	window->addElement(std::move(settingsBtn));
	window->addElement(std::move(exitBtn));

	m_currentWindow = std::move(window);
}

void Menu::createMultiplayerMenu()
{
	auto window = std::make_unique<InterfaceWindow>(sf::Vector2f(1000, 950), sf::Vector2f(100, 50));

	auto backBtn = std::make_unique<Button>(
		sf::Vector2f(280, 100), sf::Vector2f(10, 10),
		"Back", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40);
	backBtn->setCallback(BACK_TO_MAIN);

	window->addElement(std::move(backBtn));

	// Add multiplayer buttons here...

	m_currentWindow = std::move(window);
}

void Menu::createSettingsMenu()
{
	try {
		m_background.setTexture(&R_Manager::get().access<sf::Texture>("jojo-dan.png"));
	}
	catch (...) {
		m_change = false;
	}

	auto window = std::make_unique<InterfaceWindow>(sf::Vector2f(300, 600), sf::Vector2f(1400, 100));

	auto backBtn = std::make_unique<Button>(
		sf::Vector2f(280, 100), sf::Vector2f(10, 10),
		"Back", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40);
	backBtn->setCallback(BACK_TO_MAIN);

	auto plrName = std::make_unique<InterfaceInputField>(sf::Vector2f{ 300,100 },
		sf::Vector2f{ 100,100 }, R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 20);
	plrName->setText(Config::getInstance()["GameData"]["profileName"]);

	window->addElement(std::move(backBtn));
	window->addElement(std::move(plrName));

	// Add settings buttons here...

	m_currentWindow = std::move(window);
}

void Menu::start() {
	m_isRunning = false;

	try {
		m_background.setSize(sf::Vector2f(Game::get().getWindow().getSize()));
	}
	catch (...) {
		m_change = false;
	}

	switch (m_state)
	{
	case State::Base:
		createBaseMenu();
		break;
	case State::Multiplayer:
		createMultiplayerMenu();
		break;
	case State::Settings:
		createSettingsMenu();
		break;
	}
	m_currentWindow->centerElementsVertically();
	m_currentWindow->centerElementsHorizontally();

	m_isRunning = true;
}

void Menu::run()
{
	static Timer escapeDelay(500);

	if (m_change) {
		m_change = false;
		start();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escapeDelay()) {
		escapeDelay.restart();
		if (m_state != State::Base) {
			changeState(State::Base);
			return;
		}
		EXIT();
	}

	Game::get().getWindow().draw(m_background);
	if (m_currentWindow) {
		m_currentWindow->draw(Game::get().getWindow());
	}
}

void Menu::close()
{
	cout << "Menu class closed" << endl;
	m_isRunning = false;
	m_currentWindow.reset();
}