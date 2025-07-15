#pragma once

class Entity;
class Engine;

class Components {
public:
    virtual ~Components() = default;
    virtual void update(float deltatime, Entity& entity, Engine& engine) = 0;
};

class PoisonPill : public Components {
public:
    PoisonPill(float timeToDie) : maxTime(timeToDie) {
    }

    void update(float deltatime, Entity& entity, Engine& engine) override;

private:
    float elapsedSeconds{};
    float maxTime{};
};
