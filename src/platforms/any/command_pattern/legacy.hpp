#ifndef __LEGACY_HPP__
#define __LEGACY_HPP__

#include "stdafx.h"
#include <map>

class LegacyInputHandler {
public:
	void handleInput();
private:
	bool isPressed(enum BUTTON b) {
		static std::map<enum BUTTON, bool/*used*/> m = {
		{BUTTON::A, false},
		{BUTTON::B, false},
		{BUTTON::X, false},
		{BUTTON::Y, false},
		};

		return ::isPressed(m, b);
	}
};

#endif