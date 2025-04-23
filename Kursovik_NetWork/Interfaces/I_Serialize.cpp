#include "I_Serialize.h"

CEREAL_REGISTER_TYPE(I_Serialize);
CEREAL_REGISTER_TYPE(SpriteWrapper);
CEREAL_REGISTER_POLYMORPHIC_RELATION(I_Serialize, SpriteWrapper);
