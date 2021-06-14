// dllmain.cpp : Defines the entry point for the DLL application.
#include "patterned.hpp"
#include "stdafx.h"

void run_patterned() {
  Physics physics_system;
  Archivements archivement_system;
  physics_system.addObserver(&archivement_system);

  Entity hero('@');
  physics_system.updateEntity(hero);

  physics_system.rmObserver(&archivement_system);
}

int main(int argc, char *argv[]) {
  run_patterned();
  return 0;
}