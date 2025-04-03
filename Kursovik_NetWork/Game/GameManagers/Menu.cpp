#include "Menu.h"
#include "./../Game.h"

using namespace std;

// Функции-обработчики кнопок
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
    Menu::get().ChangeMode(Menu::State::Multiplayer);
}

void SETTINGS()
{
    Menu::get().ChangeMode(Menu::State::Settings);
}

void BACK_TO_MAIN()
{
    Menu::get().ChangeMode(Menu::State::Base);
}

void Menu::ChangeMode(const State& newState)
{
    Menu::get().state = newState;
    Menu::get().start(); // Перезапускаем меню с новым состоянием
}

void Menu::start() {
    std::vector<Button*> bvect;
    //O_Manager::get().clear();

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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escapeDelay())
    {
        escapeDelay.restart();
        if (state != State::Base)
        {
            ChangeMode(State::Base); // Возврат в главное меню по ESC
        }
        else
        {
            EXIT(); // Выход из игры, если уже в главном меню
        }
    }
}

void Menu::close()
{
    cout << "Menu class closed" << endl;
    isrun = false;
}