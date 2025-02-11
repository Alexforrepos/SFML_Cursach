#include "Game_Proc.h"
#include "Game.h"
#include "Level.h"
#include "Card_T.h"
#include "Zombie.h"


void Game_Proc::Run()
{
}

void Game_Proc::Close()
{
	O_Manager::get().clear();
	isrun = false;
}

void Game_Proc::Start()
{
	Ost.play();
	O_Manager::get().add_obj(new Level<9, 3>);
	O_Manager::get().add_obj(new Card_T);
	O_Manager::get().add_obj(new Zombie);

	isrun = true;
}
