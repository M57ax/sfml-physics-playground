#pragma once

#include <SFML/Graphics.hpp>

#include "component.hpp"
//  13.06.2025
//  Angefangen mit Componenten, component.hpp erstellt und soweit die Basisklasse erstellt. Auch die
//  die Erste KLasse die von Components erbt. Gedanke war hier, erstmal zu Testzwecken alle
//  componenten in die component.hpp zu packen, aufteilung in einzelne componenten erst, wenn alles
//  einigermaßen läuft und ich es verstehe Problem. Momentan noch mit der Implementierung und
//  Ausführung der Componente "poisonPill" compiliert soweit

//

// class Components;
class Engine;

class Entity {
public:
    Entity(sf::Vector2f position, sf::Vector2f velocity);
    Entity(Entity&&) = default;

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
