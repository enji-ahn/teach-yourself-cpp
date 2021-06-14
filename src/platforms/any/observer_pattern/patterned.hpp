#ifndef __PATTERNED__HPP__
#define __PATTERNED__HPP__

#include <cassert>
#include <iostream>
#include <list>

enum Force {
  GRAVITY
};

enum Event {
  EVENT_ENTITY_FELL
};

enum Archivement {
  ARCHIVEMENT_FELL_OFF_BRIDGE
};

class Entity {
public:
  Entity(char c) : c_(c) {}
  bool isOnSurface();
  void accelerate(Force force);
  void update();
  bool isHero() const {
    return c_ == '@';
  }

private:
  char c_;
};

////[[
class Observer {
public:
  virtual ~Observer() {}
  virtual void onNotify(const Entity &entity, Event event) = 0;
};

class Subject {
public:
  void addObserver(Observer *o) {
    observers_.push_back(o);
  }
  void rmObserver(Observer *o) {
    observers_.remove(o);
  }

protected:
  void notify(const Entity &entity, Event event) {
    for (auto i : observers_) {
      i->onNotify(entity, event);
    }
  }

private:
  std::list<Observer *> observers_;
};
////]]

class Physics : public Subject {
public:
  void updateEntity(Entity &entity);
};

class Archivements : public Observer {
public:
  virtual void onNotify(const Entity &entity, Event event) {
    switch (event) {
    case EVENT_ENTITY_FELL:
      if (entity.isHero() && heroIsOnBridge_) {
        unlock(ARCHIVEMENT_FELL_OFF_BRIDGE);
        heroIsOnBridge_ = !heroIsOnBridge_;
      }
      break;
    default:
      assert(false);
      break;
    }
  }

private:
  void unlock(Archivement archivement) {
    std::string archived = [archivement]() {
      switch (archivement) {
      case ARCHIVEMENT_FELL_OFF_BRIDGE:
        return "ARCHIVEMENT_FELL_OFF_BRIDGE";
      default:
        return "UNKNOWN";
      }
    }();
    std::cout << archived << " is unlocked" << std::endl;
  }

private:
  bool heroIsOnBridge_;
};

#endif