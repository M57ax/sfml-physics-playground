#include <SFML/Graphics.hpp>

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

#include "Entities/ball.hpp"
#include "Entities/particles.hpp"
#include "States/EditGameState.hpp"
#include "States/MenuGameState.hpp"
#include "States/PlayAstroGameState.hpp"
#include "States/PlayGameState.hpp"
#include "States/gameState.hpp"
#include "UI/textButtons.hpp"
#include "engine.hpp"
#include "helperFunctions.hpp"

int main() {
    Engine engine;
    std::cout << "Menu State" << std::endl;
    engine.pushState(std::make_unique<MenuGameState>(engine));
    // engine.pushState(std::make_unique<PlayGameState>(engine));

    engine.gameLoop();
    std::cout << "Nach Loop State" << std::endl;
}
