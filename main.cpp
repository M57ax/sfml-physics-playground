#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numbers>
#include <random>
#include <vector>

const sf::Vector2u windowSize(1500, 800);

constexpr int numberOfBalls = 11;
bool isGamePaused = false;
float ballSpeed = 25.F;
float maxBallSpeed{};
float slowMotionVal = 1;
float turboVal = 1;
constexpr float minSpeed = 15.0F;
constexpr float maxSpeed = 50.0F;
float minMaxSpeed = std::clamp(minMaxSpeed, minSpeed, maxSpeed);

sf::Color colorBasedOnSpeed(float speed, float minSpeed, float maxSpeed) {
    float speedInPercent = (speed - minSpeed) / (maxSpeed - minSpeed);
    speedInPercent = std::clamp(speedInPercent, 0.0F, 1.0F);  // range from 0% to 100 %

    int red = 0;
    int green = 0;
    int blue = 0;
    int maxRGBvalue = 255;

    if (speedInPercent <= 0.25F) {
        blue = maxRGBvalue;
        green = ((speedInPercent / 0.25F) * maxRGBvalue);
    } else if (speedInPercent <= 0.5F) {
        blue = ((1.0F - (speedInPercent - 0.25F) / 0.25F) * maxRGBvalue);
        green = maxRGBvalue;
    } else if (speedInPercent <= 0.75F) {
        red = (((speedInPercent - 0.50F) / 0.25F) * maxRGBvalue);
        green = maxRGBvalue;
    } else if (speedInPercent <= 1.0F) {
        green = ((1.0F - (speedInPercent - 0.75F) / 0.25F) * maxRGBvalue);
        red = maxRGBvalue;
    }
    return (sf::Color(red, green, blue));
}

class Ball {
public:
    Ball(float radius, sf::Vector2f vel, sf::Vector2f startPos, const sf::Color& color)
        : circle(radius), velocity(vel), mass(2 * radius * std::numbers::pi_v<float>) {
        circle.setFillColor(color);
        circle.setPosition(startPos);
    }

    void update(float windowSizeX, float windowSizeY, float deltatime, float maxBallSpeed,
        float slowMotion, float turboMotion, float minSpeed, float maxSpeed) {
        sf::Vector2f pos = circle.getPosition();
        float radius = circle.getRadius();

        if (pos.x < 0) {
            velocity.x = std::abs(velocity.x);
        } else if (pos.x + radius * 2 > windowSizeX) {
            velocity.x = -std::abs(velocity.x);
        }

        if (pos.y < 0) {
            velocity.y = std::abs(velocity.y);
        } else if (pos.y + radius * 2 > windowSizeY) {
            velocity.y = -std::abs(velocity.y);
        }

        pos.x += velocity.x * deltatime * maxBallSpeed * slowMotion * turboMotion;
        pos.y += velocity.y * deltatime * maxBallSpeed * slowMotion * turboMotion;

        float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        circle.setFillColor(colorBasedOnSpeed(speed, minSpeed, maxSpeed));

        circle.setPosition(pos);
    }

public:
    sf::CircleShape circle;
    sf::Vector2f velocity;
    sf::Color color;
    float mass;
};

sf::Vector2f getBallCenter(const Ball& ball) {
    return ball.circle.getPosition() +
        sf::Vector2f(ball.circle.getRadius(), ball.circle.getRadius());
}

sf::Vector2f calcVelocity(const sf::Vector2f velocityA, const sf::Vector2f velocityB,
    const sf::Vector2f posA, const sf::Vector2f posB, float MassA, float MassB) {
    return velocityA -
        ((2 * MassB) / (MassA + MassB)) * (velocityA - velocityB).dot(posA - posB) /
        (posA - posB).lengthSquared() * (posA - posB);
}

bool isCollision(const Ball& a, const Ball& b) {
    const sf::Vector2f centerBallA = getBallCenter(a);
    const sf::Vector2f centerBallB = getBallCenter(b);

    const float distanceBetweenBalls = (centerBallB - centerBallA).length();
    const float sumOfRadiiOfBalls = a.circle.getRadius() + b.circle.getRadius();

    if (sumOfRadiiOfBalls >= distanceBetweenBalls) {
        sf::Vector2f futurePosBallA = (centerBallA + a.velocity.normalized());
        sf::Vector2f futurePosBallB = (centerBallB + b.velocity.normalized());
        float futureDistanceBalls = (futurePosBallB - futurePosBallA).length();

        return futureDistanceBalls <= distanceBetweenBalls;
    }

    return false;
}

bool handleCollision(Ball& a, Ball& b) {
    if (isCollision(a, b)) {
        const sf::Vector2f centerBallA = getBallCenter(a);
        const sf::Vector2f centerBallB = getBallCenter(b);

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

Ball createRandomBall() {
    const sf::Vector2f radiusRange(12, 50);
    const sf::Vector2f velocityBall(-47.5F, 40.5F);
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
    sf::Color startColor(0, 0, 255);

    return {radius, vel, startPos, startColor};
}

void handleInput(sf::Event& event) {
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

int main() {
    sf::RenderWindow window(sf::VideoMode({windowSize.x, windowSize.y}), "Bouncing Ball");
    std::vector<Ball> balls;
    sf::Clock clock;

    // balls.push_back({20.F, {5.F, 0.F}, {100, 100}, sf::Color::Red});
    // balls.push_back({20.F, {15.F, 0.F}, {100, 150}, sf::Color::Red});
    // balls.push_back({20.F, {20.F, 0.F}, {100, 200}, sf::Color::Red});
    // balls.push_back({20.F, {25.F, 0.F}, {100, 250}, sf::Color::Red});
    // balls.push_back({20.F, {30.F, 0.F}, {100, 300}, sf::Color::Red});
    // balls.push_back({20.F, {35.F, 0.F}, {100, 350}, sf::Color::Red});
    // balls.push_back({20.F, {40.F, 0.F}, {100, 400}, sf::Color::Red});
    // balls.push_back({20.F, {45.F, 0.F}, {100, 450}, sf::Color::Red});
    // balls.push_back({20.F, {50.F, 0.F}, {100, 500}, sf::Color::Red});
    // balls.push_back({20.F, {80.F, 0.F}, {100, 550}, sf::Color::Red});
    for (int i = 1; i < numberOfBalls; ++i) {
        balls.emplace_back(createRandomBall());
    }

    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            handleInput(event.value());
        }

        float deltatime = clock.restart().asSeconds();

        if (!isGamePaused) {
            for (size_t i = 0; i < balls.size(); ++i) {
                for (size_t j = i + 1; j < balls.size(); ++j) {
                    if (handleCollision(balls[i], balls[j])) {
                    }
                }
            }

            for (auto& ball : balls) {
                ball.update(windowSize.x, windowSize.y, deltatime, maxBallSpeed, slowMotionVal,
                    turboVal, minSpeed, maxSpeed);
            }

            window.clear();
            for (auto& ball : balls) {
                window.draw(ball.circle);
            }

            window.display();
        }
    }
}
