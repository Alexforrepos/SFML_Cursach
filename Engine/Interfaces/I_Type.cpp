#include "I_Type.h"

std::pair<uint8_t, uint8_t> RANGE_PROJECTILE(uint8_t(Types::BaseProjectileType), uint8_t(Types::BaseZombieType) - 1);
std::pair<uint8_t, uint8_t> RANGE_ZOMBIE(uint8_t(Types::BaseProjectileType), uint8_t(Types::BaseZombieType) - 1);
std::pair<uint8_t, uint8_t> RANGE_PLANT(uint8_t(Types::BasePlantType), uint8_t(Types::Cart) - 1);