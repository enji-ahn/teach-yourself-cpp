// dllmain.cpp : Defines the entry point for the DLL application.
#include "patterned.hpp"
#include "stdafx.h"

void run_patterned() {
  gameLoop();
}

int main(int argc, char *argv[]) {
  run_patterned();
  return 0;
}