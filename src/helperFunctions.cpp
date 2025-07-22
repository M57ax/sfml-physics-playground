#include "helperFunctions.hpp"

#include <iostream>
#include <random>

#include "ball.hpp"
#include "engine.hpp"
#include "entity.hpp"

void createBalls(Engine& engine) {
    constexpr int numberOfBalls = 22;
    for (int i = 1; i < numberOfBalls; ++i) {
        engine.entities.emplace_back(std::make_unique<Ball>(createRandomBall()));
    }
}

Ball createRandomBall() {
    const sf::Vector2f radiusRange(12, 50);
    const sf::Vector2f velocityBall(-25.0F, 5.0F);
    const sf::Vector2i cordinatesX(0, 500);
    const sf::Vector2i cordinatesY(0, 500);

    static std::mt19937 random{static_cast<std::mt19937::result_type>(
        std::chrono::steady_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<> radiusDist{
        static_cast<int>(radiusRange.x), static_cast<int>(radiusRange.y)};
    std::uniform_real_distribution<> velocityDist{velocityBall.x, velocityBall.y};
    std::uniform_int_distribution<> xStart{cordinatesX.x, cordinatesX.y};
    std::uniform_int_distribution<> yStart{cordinatesY.x, cordinatesY.y};

    float radius(radiusDist(random));
    sf::Vector2f vel(velocityDist(random), velocityDist(random));
    sf::Vector2f startPos(xStart(random), yStart(random));

    return {radius, vel, startPos};
}
// 2 balls to test
void Engine::createTestBalls() {
    float radius1 = 30.f;
    sf::Vector2f velocity1(50.f, 0.f);
    sf::Vector2f position1(300.f, 400.f);

    float radius2 = 30.f;
    sf::Vector2f velocity2(-50.f, 0.f);
    sf::Vector2f position2(900.f, 400.f);

    entities.emplace_back(std::make_unique<Ball>(radius1, velocity1, position1));
    entities.emplace_back(std::make_unique<Ball>(radius2, velocity2, position2));
}
