#include "stdafx.h"
#include "legacy.hpp"

void LegacyInputHandler::handleInput()
{
	if (isPressed(BUTTON::X)) ::jump();
	else if (isPressed(BUTTON::Y)) ::fireGun();
	else if (isPressed(BUTTON::A)) ::swapWeapon();
	else if (isPressed(BUTTON::B)) ::lurchIneffectively();
}
