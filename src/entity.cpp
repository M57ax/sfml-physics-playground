#include "entity.hpp"

#include "component.hpp"
#include "engine.hpp"
#include "helperFunctions.hpp"

Entity::Entity(sf::Vector2f position, sf::Vector2f velocity)
    : position(position), velocity(velocity) {
}

void Entity::input(const sf::Event& event, Engine& engine) {
}

void Entity::addComponent(std::unique_ptr<Components> component) {
    components.emplace_back(std::move(component));
};


// void Entity::update(float deltatime, Engine& engine) {}
