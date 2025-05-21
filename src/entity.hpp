#pragma once

#include <SFML/Graphics.hpp>

class Engine;

class Entity {
public:
    Entity(sf::Vector2f position, sf::Vector2f velocity);

    virtual void update(float deltatime, Engine& engine) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual bool isDead() const {
        return false;
    }
    virtual ~Entity() = default;

    sf::Vector2f position;
    sf::Vector2f velocity;
};
