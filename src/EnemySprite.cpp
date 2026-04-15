#include "EnemySprite.h"
#include <iostream>

EnemySprite::EnemySprite(int x, int y) : Enemy(x, y) {
    if (!texture.loadFromFile("assets/enemy.png")) {
        std::cerr << "Warning: assets/enemy.png not found. Using red rectangle.\n";
        sf::Image img(sf::Vector2u(32, 32), sf::Color::Red);
        texture.loadFromImage(img);
    }
    sprite = std::make_unique<sf::Sprite>(texture);
    float scaleX = 32.0f / texture.getSize().x;
    float scaleY = 32.0f / texture.getSize().y;
    sprite->setScale({scaleX, scaleY});
}

void EnemySprite::draw(sf::RenderWindow& window, int tileSize) {
    sprite->setPosition(sf::Vector2f(getX() * tileSize, getY() * tileSize));
    window.draw(*sprite);
}