#include "Game.h"
#include <iostream>

void Game::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            close();
            return;
        }

        switch (m_currentState)
        {
        case State::Menu:
            if (m_menu && m_menu->isRunning())
            {
                m_menu->handleEvent(event);
            }
            break;

        case State::GameProcess:
            m_gameProcess.handleEvent(event);
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

    if (getState() == State::GameProcess && !m_gameProcess.isRunning())
        m_gameProcess.start(1);

    switch (m_currentState)
    {
    case State::Menu:
        if (m_menu) m_menu->run();
        break;

    case State::GameProcess:
        m_gameProcess.run();
        break;

    default:
        break;
    }

    m_objectManager.update();
    m_objectManager.draw(m_window);

    m_window.display();
}