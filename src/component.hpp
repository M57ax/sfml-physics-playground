#pragma once
#include <functional>

class Entity;
class Engine;

class Components {
public:
    virtual ~Components() = default;
    virtual void update(float deltatime, Entity& entity, Engine& engine) = 0;
};
class FunctionComponent : public Components {
public:
    FunctionComponent(std::function<void(float deltatime, Entity& entity, Engine& engine)>);
    void update(float deltatime, Entity& entity, Engine& engine) override;

private:
    std::function<void(float deltatime, Entity& entity, Engine& engine)> fun;
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
