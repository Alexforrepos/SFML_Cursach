#pragma once
#include "I_Object.h"
enum ZOMBE_TO_SPAWN_SCORES
{
	NORMAL_ZOMBIE_POINT = 100,
	ZOMBIE_WITH_TRAFFIC_CONE_POINT = 200,
	ZOMBIE_WITH_IRON_BUCKET_POINT = 300,
	ZOMBIE_GYMNAST_POINT = 300
};

class EnemyManager
	:public I_Object
{
	int points;
public:
	void Spawn();
	void GetPoints(int GetPoint) { this->points += points; };

	// Унаследовано через I_Object
	void Update() override;
	void SendMSG(MSG* msg) override;
	void Draw(sf::RenderWindow& win) override;
};