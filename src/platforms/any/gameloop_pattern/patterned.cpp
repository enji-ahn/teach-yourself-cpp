#include "patterned.hpp"
#include "stdafx.h"

static const auto MS_PER_UPDATE = 16;

void processInput()
{
  std::cout << "processInput a thing" << std::endl;
}

void update()
{
  std::cout << "update a thing" << std::endl;
}
void render()
{
  std::cout << "render a thing" << std::endl;
}

static float getCurrentTime()
{
    // pseudo timer
  static auto tick = 0.f;
  tick += MS_PER_UPDATE * 1.7;

  return tick;
}

/**
 * 시간에 따른 update 와 rendering 시점
 * 
 *     update update update update update update update update
 * ------|------+------+------+|-----+------+--|---+------+------
 *     render                render          render
 * 
 * 업데이트는 정확하게 고정 간격으로 진행하지만, 렌더링은 가능할 때만 함.
 */
void gameLoop()
{
  auto previous = getCurrentTime();
  auto lag = 0.f;

  while(true) {
    auto current = getCurrentTime();
    auto elapsed = current - previous;
    previous = current;
    lag += elapsed;

    processInput();

    while (lag >= MS_PER_UPDATE) {
      update();
      lag -= MS_PER_UPDATE;
    }

    render();
  }
}
