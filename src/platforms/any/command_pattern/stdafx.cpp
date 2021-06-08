#include "stdafx.h"
#include <iostream>
#include <map>

void jump() { std::cout << "Jump" << std::endl; }
void fireGun() { std::cout << "Fire" << std::endl; }
void swapWeapon() { std::cout << "Swap" << std::endl; }
void lurchIneffectively() { std::cout << "Lurch" << std::endl; }
bool isPressed(std::map<enum BUTTON, bool/*used*/>& map, enum BUTTON b) {
	if (map[b] == false) {
		map[b] = true;
		return map[b];
	}

	return false;
}
