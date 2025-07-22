#include <SFML/Graphics.hpp>

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

#include "ball.hpp"
#include "engine.hpp"
#include "helperFunctions.hpp"
#include "particles.hpp"

int main() {
    Engine engine;

    engine.gameLoop();
}
