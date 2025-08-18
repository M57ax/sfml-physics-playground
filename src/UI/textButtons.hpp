#pragma once
#include <SFML/Graphics.hpp>

class Engine;
class TextButton {
public:
    TextButton(const std::string& label, sf::Vector2f position);

    void handleInput(Engine& engine, sf::Event& event);
    void update(float deltatime, Engine& engine);
    void draw(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text text;
    bool isEditing = false;
    bool isHovering = false;
    sf::Color normalColor = sf::Color::White;
    sf::Color hoverColor = sf::Color::Yellow;
    sf::Color editingColor = sf::Color::Yellow;
};
