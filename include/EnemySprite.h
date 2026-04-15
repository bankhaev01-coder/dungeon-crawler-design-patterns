#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <memory>


class EnemySprite : public Enemy {
private:
    sf::Texture texture;
    std::unique_ptr<sf::Sprite> sprite;

public:
    EnemySprite(int x, int y);
    void draw(sf::RenderWindow& window, int tileSize) override;
};