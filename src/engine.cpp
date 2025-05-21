#include "engine.hpp"

#include <iostream>
#include <random>

#include "ball.hpp"
#include "particles.hpp"

Engine::Engine() : window(sf::VideoMode({1500, 800}), "Bouncing Ball") {
    constexpr int maxFps = 60;
    window.setFramerateLimit(maxFps);
}
void Engine::handleInput(sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        auto key = event.getIf<sf::Event::KeyPressed>()->scancode;
        if (key == sf::Keyboard::Scancode::Space) {
            isGamePaused = !isGamePaused;
        }
        if (key == sf::Keyboard::Scancode::P) {
            baseSpeedFactor = std::clamp(baseSpeedFactor += 0.3F, 0.1F, 15.F);
        }
        if (key == sf::Keyboard::Scancode::M) {
            baseSpeedFactor = std::clamp(baseSpeedFactor -= 0.3F, 0.1F, 15.F);
        }
    }
    // Camera not Used right now
    sf::Vector2f cameraRight(1.F, 0.F);
    sf::Vector2f cameraLeft(-1.F, 0.F);
    sf::Vector2f cameraUp(0.F, -1.F);
    sf::Vector2f cameraDown(0.F, 1.F);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        viewZoom.move(cameraUp);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        viewZoom.move(cameraDown);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        viewZoom.move(cameraRight);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        viewZoom.move(cameraLeft);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {
        tempModifier = 50.0F;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        tempModifier = 0.09F;
    } else {
        tempModifier = 10.0F;
    }
    normalSpeedFactor = baseSpeedFactor * tempModifier;
}

bool Engine::isCollision(const Ball& a, const Ball& b) {
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

bool Engine::handleCollision(Ball& a, Ball& b) {
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

Ball Engine::createRandomBall() {
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
// Create Particles, u can decide if the particles should spread in 360° with "spread"
// or only up and down.
void Engine::createRandomParticle(sf::Vector2f position) {
    static std::mt19937 random{static_cast<std::mt19937::result_type>(
        std::chrono::steady_clock::now().time_since_epoch().count())};

    std::uniform_real_distribution<float> spread(0.f, 2.f * 3.14f);
    std::uniform_real_distribution<float> spreadDown(1.0f, 2.1f);
    std::uniform_real_distribution<float> spreadUp(-1.0f, -2.1f);
    float spR = spread(random);
    float spU = spreadUp(random);
    float spD = spreadDown(random);

    const float speedParticle = 4.0f;
    sf::Vector2f particleSpreadRandom(std::cos(spR) * speedParticle, std::sin(spR) * speedParticle);
    sf::Vector2f particleSpreadUp(std::cos(spU) * speedParticle, std::sin(spU) * speedParticle);
    sf::Vector2f particleSpreadDown(std::cos(spD) * speedParticle, std::sin(spD) * speedParticle);
    // Chose HERE which particles should be generated:

    // entities.emplace_back(std::make_unique<Particle>(position, particleSpreadUp));
    // entities.emplace_back(std::make_unique<Particle>(position, particleSpreadDown));
    entities.emplace_back(std::make_unique<Particle>(position, particleSpreadRandom));
}

// 2 Balls to debug
void Engine::createTestBalls() {
    float radius1 = 30.f;
    sf::Vector2f velocity1(50.f, 0.f);
    sf::Vector2f position1(300.f, 400.f);

    float radius2 = 30.f;
    sf::Vector2f velocity2(-50.f, 0.f);
    sf::Vector2f position2(900.f, 400.f);

    entities.emplace_back(std::make_unique<Ball>(radius1, velocity1, position1));
    entities.emplace_back(std::make_unique<Ball>(radius2, velocity2, position2));
}

void Engine::createBalls() {
    constexpr int numberOfBalls = 22;
    for (int i = 1; i < numberOfBalls; ++i) {
        entities.emplace_back(std::make_unique<Ball>(createRandomBall()));
    }
}

void Engine::collisionHandle(float deltatime) {
    constexpr int numberOfParticles = 8;
    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            // dynamic cast checks if the object, where entities[] is pointing on,
            // is realy from type Ball, if yes ballA will will point on the object
            Ball* ballA = dynamic_cast<Ball*>(entities[i].get());
            Ball* ballB = dynamic_cast<Ball*>(entities[j].get());
            if (ballA && ballB && handleCollision(*ballA, *ballB)) {
                sf::Vector2f middleOfBallA = Ball::getBallCenter(*ballA);
                sf::Vector2f middleOfBallB = Ball::getBallCenter(*ballB);
                sf::Vector2f collisionMidPoint = (middleOfBallA + middleOfBallB) / 2.0f;
                for (int i = 0; i <= numberOfParticles; i++) {
                    createRandomParticle(collisionMidPoint);
                }
            }
        }
    }
}

void Engine::removeDeadParticle() {
    entities.erase(std::remove_if(entities.begin(), entities.end(),
                       [](const std::unique_ptr<Entity>& entity) {
                           return entity->isDead();
                       }),
        entities.end());
}

void Engine::gameLoop() {
    // viewZoom = sf::View(sf::FloatRect({100.f, 100.f}, {100.f, 100.f}));

    createBalls();
    // youse createTestBalls for test case
    // createTestBalls();
    sf::Font font("/home/schelske/vsc/firstSFML/src/roboto.ttf");
    font.openFromFile("/home/schelske/vsc/firstSFML/src/roboto.ttf");

    sf::Vector2u windowSize = window.getSize();
    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            handleInput(event.value());
        }

        float deltatime = clock.restart().asSeconds();

        int fpsValue = static_cast<int>(1.f / deltatime);
        sf::Text fps(font);
        fps.setFont(font);
        fps.setString("FPS: " + std::to_string(fpsValue));
        fps.setCharacterSize(18);
        fps.setFillColor(sf::Color::Red);

        if (!isGamePaused) {
            collisionHandle(deltatime);

            for (auto& entity : entities) {
                entity->update(deltatime, *this);
            }
            removeDeadParticle();
        }
        window.clear();
        for (auto& entity : entities) {
            entity->draw(window);
        }
        // window.setView(viewZoom);
        window.draw(fps);
        window.display();
    }
}

sf::Vector2u Engine::getWindowSize() const {
    return window.getSize();
}
