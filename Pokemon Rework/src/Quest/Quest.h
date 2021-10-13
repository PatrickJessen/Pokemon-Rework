#pragma once
#include "../Dialog/Dialog.h"

class Quest
{
public:
	Quest(std::string description, int number)
		:description(description), number(number)
	{

	}
	~Quest() = default;

	std::string GetDescription() { return description; }
	int GetNumber() 
	{ 
		return number; 
	}

	void SetIsFinnished(bool value) { finnished = value; }
	bool GetIsFinnished() { return finnished; }

private:
	std::string description;
	bool finnished = false;
	int number;
};