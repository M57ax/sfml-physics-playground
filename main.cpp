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

// TODO: Geschwindigeit der Bälle(update) mit + und - verändern, Leertaste pausiert.

class Ball {
public:
    Ball(float radius, sf::Vector2f vel, sf::Vector2f startPos, const sf::Color& color)
        : circle(radius), velocity(vel), mass(2 * radius * std::numbers::pi_v<float>) {
        circle.setFillColor(color);
        circle.setPosition(startPos);
    }

    void update(float windowSizeX, float windowSizeY) {
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

        pos.x += velocity.x;
        pos.y += velocity.y;

        circle.setPosition(pos);
    }

public:
    sf::CircleShape circle;
    sf::Vector2f velocity;
    sf::Vector2f veloChange;
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

    const sf::Vector2f originalVelocityA = a.velocity;
    const sf::Vector2f originalVelocityB = b.velocity;

    const float distanceBetweenBalls = (centerBallB - centerBallA).length();
    const float sumOfRadiiOfBalls = a.circle.getRadius() + b.circle.getRadius();

    if (sumOfRadiiOfBalls >= distanceBetweenBalls) {
        sf::Vector2f futurePosBallA = (centerBallA + a.velocity);
        sf::Vector2f futurePosBallB = (centerBallB + b.velocity);
        float futureDistanceBalls = (futurePosBallB - futurePosBallA).length();

        return futureDistanceBalls <= distanceBetweenBalls;
    }

    return false;
}

bool handleCollision(Ball& a, Ball& b) {
    if (isCollision(a, b)) {
        const sf::Vector2f posBallA = getBallCenter(a);
        const sf::Vector2f posBallB = getBallCenter(b);

        const sf::Vector2f originalVelocityA = a.velocity;
        const sf::Vector2f originalVelocityB = b.velocity;

        a.velocity =
            calcVelocity(originalVelocityA, originalVelocityB, posBallA, posBallB, a.mass, b.mass);
        b.velocity =
            calcVelocity(originalVelocityB, originalVelocityA, posBallB, posBallA, b.mass, a.mass);

        return true;
    }

    return false;
}

Ball createRandomBall() {
    const sf::Vector2f radiusRange(7, 25);
    const sf::Vector2f velocityBall(0.1, 0.14);
    const sf::Vector2i cordinatesX(0, 500);
    const sf::Vector2i cordinatesY(0, 500);
    const sf::Vector2i colors(0, 255);
    static std::mt19937 random{static_cast<std::mt19937::result_type>(
        std::chrono::steady_clock::now().time_since_epoch().count())};

    std::uniform_int_distribution<> radiusDist{
        static_cast<int>(radiusRange.x), static_cast<int>(radiusRange.y)};
    std::uniform_real_distribution<> velocityDist{velocityBall.x, velocityBall.y};
    std::uniform_int_distribution<> xStart{cordinatesX.x, cordinatesX.y};
    std::uniform_int_distribution<> yStart{cordinatesY.x, cordinatesY.y};
    std::uniform_int_distribution<> colorDist{colors.x, colors.y};

    float radius(radiusDist(random));
    sf::Vector2f vel(velocityDist(random), velocityDist(random));
    sf::Vector2f startPos(xStart(random), yStart(random));
    sf::Color color(colorDist(random), colorDist(random), colorDist(random));

    return {radius, vel, startPos, color};
}

int main() {
    const sf::Vector2u windowSize(1500, 800);  // createballs

    const int numberOfBalls = 11;

    sf::RenderWindow window(sf::VideoMode({windowSize.x, windowSize.y}), "Bouncing Ball");
    std::vector<Ball> balls;

    for (int i = 1; i < numberOfBalls; ++i) {
        balls.emplace_back(createRandomBall());
    }

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
            for (auto& ball : balls) {
                ball.velocity *= 1.001f;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
            for (auto& ball : balls) {
                ball.velocity *= 0.999f;
            }
        }

        for (size_t i = 0; i < balls.size(); ++i) {
            for (size_t j = i + 1; j < balls.size(); ++j) {
                if (handleCollision(balls[i], balls[j])) {
                    std::cout << "Kollision zwischen Ball " << i << " und Ball " << j << " erkannt!"
                              << std::endl;
                }
            }
        }

        for (auto& ball : balls) {
            ball.update(windowSize.x, windowSize.y);
        }

        window.clear();
        for (auto& ball : balls) {
            window.draw(ball.circle);
        }

        window.display();
    }
}
