#include <SFML/Graphics.hpp>

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

#include "ball.hpp"
#include "particles.hpp"

bool isGamePaused = false;

float maxBallSpeed{};
float slowMotionVal = 1;
float turboVal = 1;
constexpr float minSpeed = 5.0F;
constexpr float maxSpeed = 25.0F;
// float minMaxSpeed = std::clamp(minMaxSpeed, minSpeed, maxSpeed);

bool isCollision(const Ball& a, const Ball& b) {
    const sf::Vector2f centerBallA = Ball::getBallCenter(a);
    const sf::Vector2f centerBallB = Ball::getBallCenter(b);

    const float distanceBetweenBalls = (centerBallA - centerBallB).length();

    const float sumOfRadiiOfBalls = a.circle.getRadius() + b.circle.getRadius();

    if (sumOfRadiiOfBalls >= distanceBetweenBalls) {
        sf::Vector2f futurePosBallA = (centerBallA + a.velocity * 0.001F);
        sf::Vector2f futurePosBallB = (centerBallB + b.velocity * 0.001F);
        float futureDistanceBalls = (futurePosBallB - futurePosBallA).length();

        return futureDistanceBalls <= distanceBetweenBalls;
    }

    return false;
}

bool handleCollision(Ball& a, Ball& b) {
    if (isCollision(a, b)) {
        const sf::Vector2f centerBallA = Ball::getBallCenter(a);
        const sf::Vector2f centerBallB = Ball::getBallCenter(b);

        const sf::Vector2f originalVelocityA = a.velocity;
        const sf::Vector2f originalVelocityB = b.velocity;

        a.velocity = Ball::calcVelocity(
            originalVelocityA, originalVelocityB, centerBallA, centerBallB, a.mass, b.mass);
        b.velocity = Ball::calcVelocity(
            originalVelocityB, originalVelocityA, centerBallB, centerBallA, b.mass, a.mass);

        return true;
    }

    return false;
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

void handleInput(sf::Event& event) {
    float ballSpeed = 25.F;
    if (event.is<sf::Event::KeyPressed>()) {
        if (event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scancode::Space) {
            isGamePaused = !isGamePaused;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {
        turboVal = 10.0F;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        slowMotionVal = 0.2F;
    } else {
        slowMotionVal = 1.0F;
        turboVal = 1.0F;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
        ballSpeed *= 1.3f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
        ballSpeed *= 0.7f;
    }

    maxBallSpeed = std::clamp(ballSpeed, minSpeed, maxSpeed);
}

void createBallLoop(std::vector<Ball>& balls) {
    constexpr int numberOfBalls = 22;
    for (int i = 1; i < numberOfBalls; ++i) {
        balls.emplace_back(createRandomBall());
    }
}

void collisionHandle(std::vector<Ball>& balls, float deltatime, std::vector<Particle>& particles) {
    for (size_t i = 0; i < balls.size(); ++i) {
        for (size_t j = i + 1; j < balls.size(); ++j) {
            if (handleCollision(balls[i], balls[j])) {
                sf::Vector2f pos = Ball::getBallCenter(balls[i]);
                sf::Vector2f pos1 = Ball::getBallCenter(balls[j]);

                float radiusA = balls[i].circle.getRadius();
                float radiusB = balls[j].circle.getRadius();
                sf::Vector2f finalPos = pos + sf::Vector2f(radiusA, 0.0F);
                sf::Vector2f finalPos1 = pos1 + sf::Vector2f(radiusB, 0.0F);
                particles.emplace_back(finalPos, sf::Vector2f(-4.0f, 4.0f));
                particles.emplace_back(finalPos, sf::Vector2f(4.0f, 4.0f));
                particles.emplace_back(finalPos, sf::Vector2f(-4.0f, -4.0f));
                particles.emplace_back(finalPos, sf::Vector2f(4.0f, -4.0f));
                particles.emplace_back(finalPos1, sf::Vector2f(4.0f, 4.0f));
                particles.emplace_back(finalPos1, sf::Vector2f(4.0f, -4.0f));
                particles.emplace_back(finalPos1, sf::Vector2f(-4.0f, -4.0f));
                particles.emplace_back(finalPos1, sf::Vector2f(-4.0f, 4.0f));
            }
        }
    }
}

void gameLoop(std::vector<Ball>& balls, sf::Clock& clock, sf::RenderWindow& window,
    std::vector<Particle>& particles) {
    sf::Vector2u windowSize = window.getSize();
    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            handleInput(event.value());
        }

        float deltatime = clock.restart().asSeconds();
        std::cout << deltatime << std::endl;

        if (!isGamePaused) {
            collisionHandle(balls, deltatime, particles);
            for (auto& ball : balls) {
                ball.update(windowSize.x, windowSize.y, deltatime, maxBallSpeed, slowMotionVal,
                    turboVal, minSpeed, maxSpeed);
            }
        }
        window.clear();
        for (auto& ball : balls) {
            window.draw(ball.circle);
        }

        for (auto& particle : particles) {
            particle.draw(window);
        }
        for (auto& particle : particles) {
            particle.update(deltatime);
        }

        window.display();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode({1500, 800}), "Bouncing Ball");
    window.setFramerateLimit(60);
    std::vector<Ball> balls;
    std::vector<Particle> particles;
    sf::Clock clock;

    createBallLoop(balls);
    gameLoop(balls, clock, window, particles);
}
