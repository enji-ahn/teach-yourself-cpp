#include "patterned.hpp"
#include "stdafx.h"

void Physics::updateEntity(Entity &entity) {
  bool wasOnSurface = entity.isOnSurface();
  entity.accelerate(GRAVITY);
  entity.update();
  if (wasOnSurface && !entity.isOnSurface()) {
    notify(entity, EVENT_ENTITY_FELL);
  }
}

bool Entity::isOnSurface() {
  static bool on_surface = false;
  on_surface = !on_surface;

  return on_surface;
}

void Entity::accelerate(Force _force) {
}

void Entity::update() {
}