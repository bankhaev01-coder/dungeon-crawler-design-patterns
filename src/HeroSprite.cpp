#include "HeroSprite.h"
#include <iostream>

HeroSprite::HeroSprite(int x, int y) : Hero(x, y) {
    if (!texture.loadFromFile("assets/hero.png")) {
        std::cerr << "Warning: assets/hero.png not found. Using blue rectangle.\n";
        sf::Image img(sf::Vector2u(32, 32), sf::Color::Blue);
        texture.loadFromImage(img);
    }
    sprite = std::make_unique<sf::Sprite>(texture);
    float scaleX = 32.0f / texture.getSize().x;
    float scaleY = 32.0f / texture.getSize().y;
    sprite->setScale({scaleX, scaleY});
}

void HeroSprite::draw(sf::RenderWindow& window, int tileSize) {
    sprite->setPosition(sf::Vector2f(getX() * tileSize, getY() * tileSize));
    window.draw(*sprite);
}