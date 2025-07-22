#pragma once

#include <SFML/Graphics.hpp>

#include "component.hpp"

class Engine;

class Entity {
public:
    Entity(sf::Vector2f position, sf::Vector2f velocity);
    Entity(Entity&&) = default;

    virtual void input(const sf::Event& event, Engine& engine);
    virtual void update(float deltatime, Engine& engine) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual bool isDead() const {
        return dead;
    }
    virtual void markDead() {
        dead = true;
    }
    virtual ~Entity() = default;

    void addComponent(std::unique_ptr<Components> component);

    sf::Vector2f position;
    sf::Vector2f velocity;

    std::vector<std::unique_ptr<Components>> components;

private:
    bool dead = false;
};
