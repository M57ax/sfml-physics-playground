#include "component.hpp"

#include <iostream>

#include "entity.hpp"

void PoisonPill::update(float deltatime, Entity& entity, Engine& engine) {
    elapsedSeconds += deltatime;
    if (elapsedSeconds >= maxTime) {
        entity.markDead();
        
    }
}

FunctionComponent::FunctionComponent(
    std::function<void(float deltatime, Entity& entity, Engine& engine)> funfun)
    : fun(funfun) {
}

void FunctionComponent::update(float deltatime, Entity& entity, Engine& engine) {
    fun(deltatime, entity, engine);
}
