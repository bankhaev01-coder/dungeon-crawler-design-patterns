#include "PotionSprite.h"
#include <iostream>

PotionSprite::PotionSprite(int x, int y) : Potion(x, y) {
    if (!texture.loadFromFile("assets/potion.png")) {
        std::cerr << "Warning: assets/potion.png not found. Using green rectangle.\n";
        sf::Image img(sf::Vector2u(32, 32), sf::Color::Green);
        texture.loadFromImage(img);
    }
    sprite = std::make_unique<sf::Sprite>(texture);
    float scaleX = 32.0f / texture.getSize().x;
    float scaleY = 32.0f / texture.getSize().y;
    sprite->setScale({scaleX, scaleY});
}

void PotionSprite::draw(sf::RenderWindow& window, int tileSize) {
    sprite->setPosition(sf::Vector2f(getX() * tileSize, getY() * tileSize));
    window.draw(*sprite);
}