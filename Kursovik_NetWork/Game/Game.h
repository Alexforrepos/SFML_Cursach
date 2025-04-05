#pragma once
#include "./Utils/Config.h"
#include "./../Interfaces/I_Serialize.h"
#include "./GameManagers/GameProcess.h"
#include "./../Engine/R_Manager.h"
#include "./../Engine/O_Manager.h"
#include "./GameManagers/Menu.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Game
{
public:
	enum class State : uint8_t
	{
		None,
		Menu,
		NetWait,
		Prepare,
		GameProcess
	};

	struct GameData
	{
		std::string profileName;
		int levelUnlock = 0;
	};


private:
	sf::RenderWindow m_window;
	O_Manager& m_objectManager;
	R_Manager& m_resourceManager;
	Config& m_config;
	bool m_isRunning;
	State m_currentState;
	std::unique_ptr<Menu> m_menu;
	GameProcess m_gameProcess;
	GameData m_gameData;

	Game() :
		m_objectManager(O_Manager::get()),
		m_resourceManager(R_Manager::get()),
		m_window(sf::VideoMode(1000, 1000), "PVZ", sf::Style::Fullscreen),
		m_config(Config::getInstance()),
		m_isRunning(true),
		m_currentState(State::Prepare),
		m_menu(&Menu::get())
	{
		try {
			// Load configuration
			m_config.load("./Res/Config/Config.json");

			// Load resources
			m_resourceManager.pushFromFile(m_window, m_config["FileSystem"]["Resource"]);

			// Initialize menu
			
			setState(State::Menu);
		}
		catch (const std::exception& e) {
			std::cerr << "Game initialization error: " << e.what() << std::endl;
			m_isRunning = false;
		}
	}

public:
	~Game() = default;

	static Game& get() {
		static Game instance;
		return instance;
	}

	void run();
	void handleEvents();

	bool isRunning() const { return m_isRunning; }
	void close()
	{
		m_isRunning = false;
		saveGameData();
	}

	State getState() const { return m_currentState; }
	void setState(State state) { m_currentState = state; }

	void closeMenu() {
		if (m_menu) {
			m_menu->close();
		}
	}

	sf::RenderWindow& getWindow() { return m_window; }

	// Save game data to config before exit
	void saveGameData() {
		m_config["GameData"]["profileName"] = m_gameData.profileName;
		m_config["GameData"]["levelUnlock"] = m_gameData.levelUnlock;
		m_config.save("./Res/Config/Config.json");
	}
};