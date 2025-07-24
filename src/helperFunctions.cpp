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

void createRandomParticle(Engine& engine, sf::Vector2f position) {
    static std::mt19937 random{static_cast<std::mt19937::result_type>(
        std::chrono::steady_clock::now().time_since_epoch().count())};

    std::uniform_real_distribution<float> spread(0.f, 2.f * 3.14f);
    float spR = spread(random);
    const float speedParticle = 4.0f;
    sf::Vector2f particleSpreadRandom(std::cos(spR) * speedParticle, std::sin(spR) * speedParticle);
    auto particle = std::make_unique<Particle>(position, particleSpreadRandom);
    particle->addComponent(std::make_unique<PoisonPill>(0.45f));
    engine.newEntities.emplace_back(std::move(particle));
}  // MANU FRAGEN

void collisionHandle(Engine& engine, float deltatime) {
    constexpr int numberOfParticles = 8;
    for (size_t i = 0; i < engine.entities.size(); ++i) {
        for (size_t j = i + 1; j < engine.entities.size(); ++j) {
            Ball* ballA = dynamic_cast<Ball*>(engine.entities[i].get());
            Ball* ballB = dynamic_cast<Ball*>(engine.entities[j].get());
            if (ballA && ballB && handleCollision(*ballA, *ballB)) {
                sf::Vector2f middleOfBallA = Ball::getBallCenter(*ballA);
                sf::Vector2f middleOfBallB = Ball::getBallCenter(*ballB);
                sf::Vector2f collisionMidPoint = (middleOfBallA + middleOfBallB) / 2.0f;
                for (int i = 0; i <= numberOfParticles; i++) {
                    createRandomParticle(engine, collisionMidPoint);  // MANU FRAGEN
                }
            }
        }
    }
}

// 2 balls to test
// void createTestBalls() {
//     float radius1 = 30.f;
//     sf::Vector2f velocity1(50.f, 0.f);
//     sf::Vector2f position1(300.f, 400.f);

//     float radius2 = 30.f;
//     sf::Vector2f velocity2(-50.f, 0.f);
//     sf::Vector2f position2(900.f, 400.f);

//     entities.emplace_back(std::make_unique<Ball>(radius1, velocity1, position1));
//     entities.emplace_back(std::make_unique<Ball>(radius2, velocity2, position2));
// }

bool handleCollision(Ball& a, Ball& b) {
    if (isCollision(a, b)) {
        const sf::Vector2f centerBallA = Ball::getBallCenter(a);
        const sf::Vector2f centerBallB = Ball::getBallCenter(b);

        const sf::Vector2f originalVelocityA = a.velocity;
        const sf::Vector2f originalVelocityB = b.velocity;

        a.velocity = calcVelocity(
            originalVelocityA, originalVelocityB, centerBallA, centerBallB, a.mass, b.mass);
        b.velocity = calcVelocity(
            originalVelocityB, originalVelocityA, centerBallB, centerBallA, b.mass, a.mass);

        return true;
    }

    return false;
}

bool isCollision(const Ball& a, const Ball& b) {
    const sf::Vector2f centerBallA = Ball::getBallCenter(a);
    const sf::Vector2f centerBallB = Ball::getBallCenter(b);

    const float distanceBetweenBalls = (centerBallA - centerBallB).length();

    const float sumOfRadiiOfBalls = a.circle.getRadius() + b.circle.getRadius();

    // prevents, that the time between the collision checks is to long
    if (sumOfRadiiOfBalls >= distanceBetweenBalls) {
        sf::Vector2f futurePosBallA = (centerBallA + a.velocity * 0.001F);
        sf::Vector2f futurePosBallB = (centerBallB + b.velocity * 0.001F);
        float futureDistanceBalls = (futurePosBallB - futurePosBallA).length();

        return futureDistanceBalls <= distanceBetweenBalls;
    }

    return false;
}

void handleWallCollision(Ball& ball, float windowSizeX, float windowSizeY) {
    sf::Vector2f pos = ball.circle.getPosition();
    float radius = ball.circle.getRadius();

    if (pos.x < 0) {
        ball.velocity.x = std::abs(ball.velocity.x);
    } else if (pos.x + radius * 2 > windowSizeX) {
        ball.velocity.x = -std::abs(ball.velocity.x);
    }

    if (pos.y < 0) {
        ball.velocity.y = std::abs(ball.velocity.y);
    } else if (pos.y + radius * 2 > windowSizeY) {
        ball.velocity.y = -std::abs(ball.velocity.y);
    }
}

// calf Functions
float calcSpeedValue(float speed, float minSpeed, float maxSpeed) {
    return std::clamp((speed - minSpeed) / (maxSpeed - minSpeed), 0.0f, 1.0f);
}

sf::Color colorBasedOnSpeed(float speedPercentage) {
    int red = 0;
    int green = 0;
    int blue = 0;
    const int maxRGBvalue = 255;

    if (speedPercentage <= 0.25F) {
        blue = maxRGBvalue;
        green = ((speedPercentage / 0.25F) * maxRGBvalue);
    } else if (speedPercentage <= 0.5F) {
        blue = ((1.0F - (speedPercentage - 0.25F) / 0.25F) * maxRGBvalue);
        green = maxRGBvalue;
    } else if (speedPercentage <= 0.75F) {
        red = (((speedPercentage - 0.50F) / 0.25F) * maxRGBvalue);
        green = maxRGBvalue;
    } else if (speedPercentage <= 1.0F) {
        green = ((1.0F - (speedPercentage - 0.75F) / 0.25F) * maxRGBvalue);
        red = maxRGBvalue;
    }
    return (sf::Color(red, green, blue));
}

sf::Vector2f calcVelocity(const sf::Vector2f velocityA, const sf::Vector2f velocityB,
    const sf::Vector2f posA, const sf::Vector2f posB, float MassA, float MassB) {
    return velocityA -
        ((2 * MassB) / (MassA + MassB)) * (velocityA - velocityB).dot(posA - posB) /
        (posA - posB).lengthSquared() * (posA - posB);
}
