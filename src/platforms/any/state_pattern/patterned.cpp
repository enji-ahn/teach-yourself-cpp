#include "patterned.hpp"
#include "stdafx.h"

Heroine::Heroine() : state_(new StandState()) {}
void Heroine::handleInput(Input input) {
  state_ = state_->handleInput(*this, input);
}

void Heroine::update() {
  state_->update(*this);
}

std::unique_ptr<HeroineState> StandState::handleInput(Heroine &heroine, Input input) {
  if (input == PRESS_DOWN) {
    heroine.setGraphics(IMAGE_DUCK);
    return std::unique_ptr<HeroineState>(new DuckingState());
  } else if (input == PRESS_B) {
    heroine.setGraphics(IMAGE_JUMP);
    return std::unique_ptr<JumpState>(new JumpState());
  }
  assert(false);
}

void StandState::update(Heroine &heroine) {
  std::cout << "Stand" << std::endl;
}

std::unique_ptr<HeroineState> DuckingState::handleInput(Heroine &heroine, Input input) {
  if (input == RELEASE_DOWN) {
    heroine.setGraphics(IMAGE_STAND);
    return std::unique_ptr<HeroineState>(new StandState());
  }
  assert(false);
}
void DuckingState::update(Heroine &heroine) {
  std::cout << "Duck" << std::endl;

  chargingTime_++;
  if (chargingTime_ > MAX_CHARGE) {
    heroine.superBomb();
  }
}

std::unique_ptr<HeroineState> JumpState::handleInput(Heroine &heroine, Input input) {
  if (input == PRESS_DOWN) {
    heroine.setGraphics(IMAGE_DIVE);
    return std::unique_ptr<HeroineState>(new DiveState());
  }
  assert(false);
}
void JumpState::update(Heroine &heroine) {
  std::cout << "Jump" << std::endl;
}
std::unique_ptr<HeroineState> DiveState::handleInput(Heroine &heroine, Input input) {
  return std::unique_ptr<HeroineState>(new StandState());
}
void DiveState::update(Heroine &heroine) {
  std::cout << "Dive" << std::endl;
}
