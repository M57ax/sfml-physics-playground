#include <SFML/Graphics.hpp>
#include <catch2/catch_test_macros.hpp>

#include "ball.hpp"
TEST_CASE("min ball speed") {
    float speed = 5.0f;
    float minSpeed = 5.0f;
    float maxSpeed = 25.0f;
    float speedPercentage = Ball::calcSpeedvalue(speed, minSpeed, maxSpeed);
    REQUIRE(Ball::colorBasedOnSpeed(speedPercentage) == sf::Color(0, 0, 255));  // blue
}

TEST_CASE("mid ball speed") {
    float speed = 15.0f;
    float minSpeed = 5.0f;
    float maxSpeed = 25.0f;
    float speedPercentage = Ball::calcSpeedvalue(speed, minSpeed, maxSpeed);
    REQUIRE(Ball::colorBasedOnSpeed(speedPercentage) == sf::Color(0, 255, 0));  // green
}

TEST_CASE("max ball speed") {
    float speed = 25.0f;
    float minSpeed = 5.0f;
    float maxSpeed = 25.0f;
    float speedPercentage = Ball::calcSpeedvalue(speed, minSpeed, maxSpeed);
    REQUIRE(Ball::colorBasedOnSpeed(speedPercentage) == sf::Color(255, 0, 0));  // red
}

TEST_CASE("turquoise ball") {
    float speed = 10.0f;
    float minSpeed = 5.0f;
    float maxSpeed = 25.0f;
    float speedPercentage = Ball::calcSpeedvalue(speed, minSpeed, maxSpeed);
    REQUIRE(Ball::colorBasedOnSpeed(speedPercentage) == sf::Color(0, 255, 255));  // turquoise
}

TEST_CASE("yellow ball") {
    float speed = 20.0f;
    float minSpeed = 5.0f;
    float maxSpeed = 25.0f;
    float speedPercentage = Ball::calcSpeedvalue(speed, minSpeed, maxSpeed);
    REQUIRE(Ball::colorBasedOnSpeed(speedPercentage) == sf::Color(255, 255, 0));  // yellow
}
