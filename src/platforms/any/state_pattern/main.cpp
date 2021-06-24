// dllmain.cpp : Defines the entry point for the DLL application.
#include "patterned.hpp"
#include "stdafx.h"

void run_patterned() {
  Heroine heroine;
  heroine.handleInput(Input::PRESS_DOWN);
  for (auto i = 0; i < 5; ++i) { heroine.update(); }
  heroine.handleInput(Input::RELEASE_DOWN);
  heroine.update();
  heroine.handleInput(Input::PRESS_B);
  heroine.update();
  heroine.handleInput(Input::PRESS_DOWN);
  heroine.update();
}

int main(int argc, char *argv[]) {
  run_patterned();
  return 0;
}