#include "Menu.h"
#include "Game.h"
#include "ResourceManager.h"  
#include "MSG_Manager.h"
#include "MSG.h"
#include "O_Manager.h"

void START()
{
    Game::Get().ChangeRunMode(Game::RUNMODE::RUNMODE_GAME);
}


void Menu::Start()
{
    isstarted = true;
    O_Manager::get().clear();

    if (!buttons.empty())
    {
        for (auto b : buttons)
            delete b;
        buttons.clear();
    }

    buttons.clear();
    buttons.push_back(new Button(
        sf::Text("Start", *(Res_Manager::get().get_access<sf::Font*>("PaluiSPDemo-Bold.otf")), 40),
        sf::Vector2f(300, 100),    
        sf::Vector2f(1400, 150),   
        START                    
    ));

    for (auto b : buttons)
        MSG_Manager::get().Recieve(new MSG(MSG_TYPE_CREATE(b, nullptr)));
}

void Menu::Run()
{
   /// тут ошибка ты в функции старта уже добавил в очередь обработки все кнопки
   /* for (auto b : buttons)
    {
        b->Update();
    }*/
}

void Menu::Close()
{
    O_Manager::get().clear();
}
