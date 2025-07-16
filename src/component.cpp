#include "component.hpp"

#include <iostream>

#include "entity.hpp"

void PoisonPill::update(float deltatime, Entity& entity, Engine& engine) {
    elapsedSeconds += deltatime;
    if (elapsedSeconds >= maxTime) {
        entity.markDead();
    }
}
