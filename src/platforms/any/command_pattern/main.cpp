// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "legacy.hpp"
#include "patterned.hpp"

void run_legacy() {
	LegacyInputHandler handler;
	handler.handleInput();
	handler.handleInput();
	handler.handleInput();
	handler.handleInput();
}

void run_patterned() {
	PatternedInputHandler handler;
	handler.assignButton(BUTTON::A, new JumpCommand);
	handler.assignButton(BUTTON::B, new SwapWeaponCommand);
	handler.assignButton(BUTTON::X, new FireCommand);
	handler.assignButton(BUTTON::Y, new LurchCommand);
	handler.handleInput();
	handler.handleInput();
	handler.handleInput();
	handler.handleInput();

}

int main(int argc, char *argv[]) {
	run_legacy();
	run_patterned();
  return 0;
}