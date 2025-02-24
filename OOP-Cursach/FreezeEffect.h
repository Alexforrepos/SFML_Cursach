#pragma once
#include "Effect.h"

class FreezeEffect : public Effect
{
	FreezeEffect(const Timer& time_to_die, Object* target)
		: time_to_die(time_to_die), target(target)
	{};
	void effect();
};

