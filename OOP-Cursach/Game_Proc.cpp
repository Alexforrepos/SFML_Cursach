#include "Game_Proc.h"
#include "Game.h"
#include "Level.h"
#include "Card_T.h"
#include "Zombie.h"
#include "Sun.h"


void Game_Proc::Run()
{
	static Timer time_to_click(1000);
	if (Config_load::getconfig().get().at("SunOnLeftButton").get<int>())
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && time_to_click())
		{
			MSG_Manager::get().add(new
				MSG(MSG_TYPE_CREATE(new Sun((sf::Vector2f)sf::Mouse::getPosition(),
					(900)), nullptr)));
			time_to_click.restart();
		}
	std::string SunCountText = "SUN:";
	SunCountText += std::to_string(Sun_value);

	sf::Text SunCount(SunCountText, Res_Manager::get().get_access<sf::Font>("BantyBold.ttf"));
	SunCount.setPosition(100, 0);
	Game::Get().win.draw(SunCount);
}

void Game_Proc::Close()
{
	O_Manager::get().clear();
	isrun = false;
}

void Game_Proc::Start()
{
	if (Config_load::getconfig().get().at("SoundOn").get<int>())
		Ost.play();
	O_Manager::get().add_obj(new Level<9, 5>);
	O_Manager::get().add_obj(new Card_T({200,200}, Peashooter));
	O_Manager::get().add_obj(new Card_T({ 400,200 }, Repeater));
	O_Manager::get().add_obj(new Card_T({ 600,200 }, Showel));
	O_Manager::get().add_obj(new Zombie);

	isrun = true;
}
