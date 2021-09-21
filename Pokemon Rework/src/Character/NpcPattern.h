#pragma once
#include "../Core/Vector2.h"
enum class AnimationDirection
{
	UP, DOWN, LEFT, RIGHT
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