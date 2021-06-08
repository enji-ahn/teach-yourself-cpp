// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#if defined(_MSC_VER)

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#endif

// reference additional headers your program requires here
#include <map>

enum class BUTTON {
	X,
	Y,
	A,
	B
};

void jump();
void fireGun();
void swapWeapon();
void lurchIneffectively();

bool isPressed(std::map<enum BUTTON, bool/*used*/>& map, enum BUTTON b);