#pragma once
#include <memory>
#include <vector>

#include "../entity.hpp"

class Engine;

class GameState {
public:
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> newEntities;

    virtual ~GameState() = default;

    virtual void handleInput(Engine& engine, sf::Event& event) = 0;

    void addEntity(std::unique_ptr<Entity> e) {
        newEntities.emplace_back(std::move(e));
    }

    void pushNewEntities() {
        for (auto& e : newEntities) {
            entities.emplace_back(std::move(e));
        }
        newEntities.clear();
    }

    std::vector<std::unique_ptr<Entity>>& getEntities() {
        return entities;
    }
};
