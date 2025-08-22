#pragma once
#include <SFML/Graphics.hpp>

#include "../entity.hpp"

class Engine;
class GameState;
class TextButton : public Entity {
public:
    using Callback = std::function<void(Engine&)>;
    TextButton(const std::string& label, sf::Vector2f position, Callback onClick = nullptr);

    void input(const sf::Event& event, Engine& engine) override;
    void update(float deltatime, Engine& engine) override;
    void draw(sf::RenderWindow& window) const override;

private:
    sf::Font font;
    sf::Text text;
    bool isEditing = false;
    bool isHovering = false;
    sf::Color normalColor = sf::Color::White;
    sf::Color hoverColor = sf::Color::Yellow;
    sf::Color editingColor = sf::Color::Yellow;
    Callback onClick;
};
