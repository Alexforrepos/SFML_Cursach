#include "EnemyManager.h"

void EnemyManager::Spawn()
{
	Zombie* newZombie = new Zombie();
	MSG_Manager::getmger()->add(new MSG(MSG_TYPE_CREATE(newZombie, this)));
}

void EnemyManager::Update()
{
	if (spawn())
	{
		Spawn();
		spawn.restart();
	}
}

void EnemyManager::SendMSG(MSG* msg)
{
}

void EnemyManager::Draw(sf::RenderWindow& win)
{
}
