#include "./Game.h"
#include <iostream>

using namespace std;
using namespace sf;

void Game::handleEvents()
{
	Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			close();
			return;
		}

	
		switch (m_currentState)
		{
		case State::Menu:
			if (m_menu && m_menu->isRunning())
			{
				m_menu->get().m_currentWindow->handleEvent(event);
			}
			break;

		case State::GameProcess:
			// Forward events to game process if needed
			break;

		default:
			break;
		}
	}
}

void Game::run()
{
	m_window.clear();


	handleEvents();

	
	if (getState() == State::Menu && m_menu && !m_menu->isRunning())
		m_menu->start();

	if (getState() == State::GameProcess && !m_gameProcess.isRun())
		m_gameProcess.start();

	
	switch (m_currentState)
	{
	case State::None:

		break;

	case State::Menu:
		if (m_menu) {
			m_menu->run();
		}
		break;

	case State::NetWait:
		
		break;

	case State::GameProcess:
		m_gameProcess.run();
		break;

	default:
		break;
	}

	// Update and draw objects
	m_objectManager.update();
	m_objectManager.draw(m_window);

	m_window.display();
}