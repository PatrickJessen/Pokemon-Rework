#pragma once
#include "Moves/Move.h"

class LearnableMove
{
public:
	LearnableMove(int level, Move* move)
		: level(level), move(move)
	{

	}
	int level;
	Move* move;
};