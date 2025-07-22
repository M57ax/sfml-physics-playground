#pragma once

#include "ball.hpp"
#include "engine.hpp"
#include "entity.hpp"
class Engine;
using EntityList = std::vector<std::unique_ptr<Entity>>;

void createBalls(Engine& engine);
void createTestBalls();
Ball createRandomBall();
