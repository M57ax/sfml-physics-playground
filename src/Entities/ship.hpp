#pragma once

#include <SFML/Graphics.hpp>

#include "../entity.hpp"

class Ship : public Entity {
public:
    Ship(sf::Vector2f startPos, sf::Vector2f initialVelocity = {0.f, 0.f});
    Ship(const Ship&) = delete;
    Ship(Ship&&) = default;
    void input(const sf::Event& event, Engine& engine) override;
    void update(float deltatime, Engine& engine) override;
    void draw(sf::RenderWindow& window) const override;

    static sf::Vector2f getShipCenter(const Ship& ship);

    sf::CircleShape playerShip;
    sf::Color color;

    float shipWeigth = 120.f;
    float targetWeigth = 550.f;

private:
    float m_shipSpeed = 3.f;
    float m_shipBoost = m_shipSpeed * 3;
};
