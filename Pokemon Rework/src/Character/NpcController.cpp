#include "NpcController.h"

NpcController::NpcController(Character* character)
	:character(character)
{
}

NpcController::~NpcController()
{
}

void NpcController::Update()
{
	if (state == NpcState::Idle)
	{
		idleTimer += Window::GetDeltatime();
		if (idleTimer > timeBetweenWalking)
		{
			idleTimer = 0;
			character->
		}
	}
}
