#pragma once
#include "Moves/Type.h"

class TypeChart
{
public:
	static float GetEffectiveness(Type attackType, Type defenseType);
};