#pragma once
#include "Effect.h"


class FreezeEffect
	:public Effect
{

	FreezeEffect()
		:Effect(200)
	{

	}


	void influence(Zombie& target) override;
};

