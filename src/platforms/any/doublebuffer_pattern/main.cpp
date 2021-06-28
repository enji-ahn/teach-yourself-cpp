// dllmain.cpp : Defines the entry point for the DLL application.
#include "patterned.hpp"
#include "stdafx.h"

void run_patterned() {
  auto scene = Scene();
  for (int i = 0; i < 2; ++i) {
    scene.draw();
    auto pixels = scene.getBuffer().getPixels();
    auto w = scene.getBuffer().WIDTH;
    auto h = scene.getBuffer().HEIGHT;
    for (auto i = 0; i < w * h; ++i) {
      if (i > 0 && i % w == 0) {
        std::cout << std::endl;
      }
      std::cout << ((pixels[i] == 0xFF /*WHITE*/) ? " " : "■");
    }
    std::cout << std::endl;
  }
}

int main(int argc, char *argv[]) {
  run_patterned();
  return 0;
}