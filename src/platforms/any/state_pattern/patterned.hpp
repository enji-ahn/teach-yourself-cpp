#ifndef __PATTERNED__HPP__
#define __PATTERNED__HPP__

#include <cassert>
#include <iostream>
#include <list>
#include <memory>

enum Image {
  IMAGE_STAND, // 서 있는 이미지
  IMAGE_JUMP,  // 점프 이미지
  IMAGE_DUCK,  // 엎드린 이미지
  IMAGE_DIVE   // 내려찍는 이미지
};

enum Input {
  PRESS_A,
  PRESS_B,
  PRESS_X,
  PRESS_Y,
  PRESS_UP,
  PRESS_DOWN,
  PRESS_LEFT,
  PRESS_RIGHT,
  RELEASE_A,
  RELEASE_B,
  RELEASE_X,
  RELEASE_Y,
  RELEASE_UP,
  RELEASE_DOWN,
  RELEASE_LEFT,
  RELEASE_RIGHT,
};

class HeroineState; // forward declaration

class Heroine {
public:
  Heroine();
  void setGraphics(Image image) {
    std::cout << "image : " << image << std::endl;
  }
  void superBomb() {
    std::cout << "Super bombed!!" << std::endl;
  }

  virtual void handleInput(Input input);
  virtual void update();

private:
  std::unique_ptr<HeroineState> state_;
};

class HeroineState {
public:
  virtual ~HeroineState() {}
  virtual std::unique_ptr<HeroineState> handleInput(Heroine &heroine, Input input) { return nullptr; }
  virtual void update(Heroine &heroine) {}
};

// Finite State Machine
//
//    ┌──Press ▼──┐┌──Press B──┐┌──Press ▼──┐
//    ▼           ││           ▼│           ▼
//  [Duck]      [Stand]      [Jump]       [Dive]
//    │           ▲
//    └─Release ▼─┘

class StandState : public HeroineState {
public:
  StandState() {}
  virtual std::unique_ptr<HeroineState> handleInput(Heroine &heroine, Input input);
  virtual void update(Heroine &heroine);
};

class DuckingState : public HeroineState {
public:
  DuckingState() : chargingTime_(0) {}
  virtual std::unique_ptr<HeroineState> handleInput(Heroine &heroine, Input input);
  virtual void update(Heroine &heroine);

private:
  int chargingTime_;
  const int MAX_CHARGE = 3;
};

class JumpState : public HeroineState {
public:
  JumpState() {}
  virtual std::unique_ptr<HeroineState> handleInput(Heroine &heroine, Input input);
  virtual void update(Heroine &heroine);
};

class DiveState : public HeroineState {
public:
  DiveState() {}
  virtual std::unique_ptr<HeroineState> handleInput(Heroine &heroine, Input input);
  virtual void update(Heroine &heroine);
};

#endif