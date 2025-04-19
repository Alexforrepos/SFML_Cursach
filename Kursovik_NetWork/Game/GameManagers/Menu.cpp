#include "Menu.h"
#include "./../Game.h"

using namespace std;

// Button callbacks
#pragma region CALLBACKS
void START()
{
	Menu::get().changeState(Menu::State::Start);
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

void LEVEL1()
{
	Game::get().setState(Game::State::GameProcess);
	Menu::get().close();
	Game::get().getGameProcess().start(1);
}

void LEVEL2()
{
	Game::get().setState(Game::State::GameProcess);
	Menu::get().close();
	Game::get().getGameProcess().start(2);
}

#pragma endregion


Menu::Menu() :
	m_state(State::Base),
	m_isRunning(false),
	m_change(false),
	m_background(sf::Vector2f(0, 0)),
	m_music(R_Manager::get().access<sf::Music>("Greenpath.mp3"))
{
	m_music.setLoop(true);
	m_music.setVolume(40);
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
	m_background.setScale(1, 1);

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

	m_currentWindow->centerElementsVertically();
	m_currentWindow->centerElementsHorizontally();
}

void Menu::createMultiplayerMenu()
{
	this->m_background.setTexture(&R_Manager::get().access<sf::Texture>("IvtClub.png"));
	m_background.setScale(0.1,0.1);
	auto window = std::make_unique<InterfaceWindow>(sf::Vector2f(1000, 950), sf::Vector2f(100, 50));

	auto backBtn = std::make_unique<Button>(
		sf::Vector2f(280, 100), sf::Vector2f(10, 10),
		"Back", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40);
	backBtn->setCallback(BACK_TO_MAIN);

	window->addElement(std::move(backBtn));

	// Add multiplayer buttons here...

	m_currentWindow = std::move(window);
	m_currentWindow->centerElementsVertically();
	m_currentWindow->centerElementsHorizontally();

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
	m_background.setScale(1, 1);

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

	m_currentWindow->centerElementsVertically();
	m_currentWindow->centerElementsHorizontally();
}

void Menu::createStartMenu()
{
	auto window = std::make_unique<InterfaceWindow>(sf::Vector2f(1400, 800), sf::Vector2f(100, 100));

	int Level_q = Config::getInstance()["Level"]["count"];
	std::function<void()> Callbacks[] = { LEVEL1 ,LEVEL2 };
	m_background.setScale(1, 1);
	
	for (int i = 0; i < Level_q; i++)
	{
		string Level = "Level " + std::to_string(i + 1);
		auto button = std::make_unique<Button>(sf::Vector2f{ 1300,200 }, sf::Vector2f{},
			Level,
			R_Manager::get().access<sf::Font>("BantyBold.ttf"), 40);
		button->setCallback(Button::Callback(Callbacks[i]));
		window->addElement(std::move(button));
	}

	auto backBtn = std::make_unique<Button>(
		sf::Vector2f(280, 100), sf::Vector2f(10, 10),
		"Back", R_Manager::get().access<sf::Font>("PaluiSPDemo-Bold.otf"), 40);
	backBtn->setCallback(BACK_TO_MAIN);
	window->addElement(std::move(backBtn));

	m_currentWindow = std::move(window);
	m_currentWindow->centerElementsVertically();
	m_currentWindow->centerElementsHorizontally();
}
void Menu::start() {
	m_isRunning = false;
	if (m_music.getStatus() != sf::Music::Playing) m_music.play();

	try {
		m_background.setSize(sf::Vector2f(Game::get().getWindow().getSize()));
	}
	catch (...) {
		m_change = false;
	}

	switch (m_state) {
	case State::Base: createBaseMenu(); break;
	case State::Multiplayer: createMultiplayerMenu(); break;
	case State::Settings: createSettingsMenu(); break;
	case State::Start: createStartMenu(); break;
	}

	m_isRunning = true;
}

void Menu::run() {
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
		Game::get().close();
	}

	Game::get().getWindow().draw(m_background);
	if (m_currentWindow) {
		m_currentWindow->draw(Game::get().getWindow());
	}
}

void Menu::close()
{
	cout << "Menu class closed" << endl;
	m_music.stop();
	m_isRunning = false;
	m_currentWindow.reset();
}