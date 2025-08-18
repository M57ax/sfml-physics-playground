#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <functional>
#include <stack>

#include "Entities/ball.hpp"
#include "Entities/fps-counter.hpp"
#include "Entities/particles.hpp"
#include "States/gameState.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "helperFunctions.hpp"

using EntityList = std::vector<std::unique_ptr<Entity>>;
// 25.7: gameState.hpp wurde als Abstrakte Basisklasse für die States implementiert.
// Engine ist ja an sich das Game. Zusätzlich wurde noch der erste State namens MenuGameState
// eingebaut in DIESE file(kurz vor der gameLoop) habe ich bereits alle basisklassen funktionen
// eingebaut, diese sind virtual und werden hier in overwritten.
// jetzt dann nochmal Binpress tutorial ansehen und versuchen das Menü als ersten einzublenden
class GameState;

class Engine {
    sf::Clock clock;

    bool isGamePaused = false;
    float deltatime = 0.0f;
    float baseSpeedFactor = 1.0F;  //
    float tempModifier = 1.0F;     //

    void handleInput(const sf::Event& event);

    void removeDeadEntities();
    void createInputHandlers();

public:
    sf::RenderWindow window;
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> newEntities;
    Engine();
    void gameLoop();
    std::stack<std::unique_ptr<GameState>> states;
    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void clearAll();
    void changeState(std::unique_ptr<GameState> state);
    GameState* currentState();
    sf::Vector2u getWindowSize() const;
    std::unordered_map<std::string, std::function<void(const sf::Event&, Engine&)>> inputHandler;
    void setTempModifier(float modifier) {
        tempModifier = modifier;
    }

    bool setPaused(bool isPaused) {
        isGamePaused = isPaused;
        return isGamePaused;
    }

    bool isPaused() const {
        return isGamePaused;
    }

    float getBaseSpeedFactor() const {
        return baseSpeedFactor;
    }

    void setBaseSpeedFactor(float baseModifier) {
        baseSpeedFactor = baseModifier;
    }

    float getDeltatime() const {
        return deltatime;
    }

    float keyInputSpeed{};
    float extraSpeedFactor = 2.F;
    float minSpeed = 5.0F;
    float maxSpeed = 15.0F;
};
