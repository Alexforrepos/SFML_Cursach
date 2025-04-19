#pragma once
#include <vector>



enum class Types
	: uint8_t
{
	None = 0,
	/*Level*/ Level,
	/*Star_Projectiles types*/ BaseProjectileType,
	/*Start ZombieClass*/ BaseZombieType,
	/*Start PlantTypes*/ BasePlantType,
	Cart,
	Hologram

};

extern std::pair<uint8_t, uint8_t> RANGE_PROJECTILE;
extern std::pair<uint8_t, uint8_t> RANGE_ZOMBIE;
extern std::pair<uint8_t, uint8_t> RANGE_PLANT;

static bool isInRange(Types type, std::pair<uint8_t, uint8_t> range)
{ return uint8_t(type) >= range.first && uint8_t(type) <= range.second; };


class I_Type
{
public:

	//метод который позвозяет узнать тип наследуемого объекта
	virtual int type() = 0;
	virtual ~I_Type() = default;
};

