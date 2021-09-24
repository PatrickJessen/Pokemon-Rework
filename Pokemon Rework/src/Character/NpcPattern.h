#pragma once
#include "../Core/Vector2.h"
enum class AnimationDirection
{
	DOWN, UP, LEFT, RIGHT, NONE
};

class NpcPattern
{
public:
	NpcPattern(Vector2 vector2, AnimationDirection direction)
		:vector2(vector2), direction(direction)
	{}
	Vector2 vector2;
	AnimationDirection direction;
};