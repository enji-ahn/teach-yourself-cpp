#include "stdafx.h"
#include "patterned.hpp"

void PatternedInputHandler::handleInput()
{
	if (isPressed(BUTTON::X)) buttonX_->execute();
	else if (isPressed(BUTTON::Y)) buttonY_->execute();
	else if (isPressed(BUTTON::A)) buttonA_->execute();
	else if (isPressed(BUTTON::B)) buttonB_->execute();
}