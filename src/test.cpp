#include <SFML/Graphics.hpp>
#include <catch2/catch_test_macros.hpp>

#include "ball.hpp"

TEST_CASE("min ball speed") {
    REQUIRE(Ball::colorBasedOnSpeed(5.0f, 5.0f, 25.0f) == sf::Color(0, 0, 255));  // blue
}
TEST_CASE("mid ball speed") {
    REQUIRE(Ball::colorBasedOnSpeed(15.0F, 5.0F, 25.0F) == sf::Color(0, 255, 0));  // green
}
TEST_CASE("max ball speed") {
    REQUIRE(Ball::colorBasedOnSpeed(25.0F, 5.0F, 25.0F) == sf::Color(255, 0, 0));  // red
}
TEST_CASE("turquoise ball") {
    REQUIRE(Ball::colorBasedOnSpeed(10.0F, 5.0F, 25.0F) == sf::Color(0, 255, 255));  // turquoise
}
TEST_CASE("yellow ball") {
    REQUIRE(Ball::colorBasedOnSpeed(20.0F, 5.0F, 25.0F) == sf::Color(255, 255, 0));  // yellow
}
