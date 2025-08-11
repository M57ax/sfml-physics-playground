#include <SFML/Graphics.hpp>

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

#include "MenuGameState.hpp"
#include "PlayGameState.hpp"
#include "ball.hpp"
#include "engine.hpp"
#include "gameState.hpp"
#include "helperFunctions.hpp"
#include "particles.hpp"

int main() {
    Engine engine;
    std::cout << "Menu State" << std::endl;
    engine.pushState(std::make_unique<MenuGameState>(engine));
    // engine.pushState(std::make_unique<PlayGameState>(engine));

    engine.gameLoop();
    std::cout << "Nach Loop State" << std::endl;
}
