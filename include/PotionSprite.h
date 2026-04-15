#pragma once
#include "Potion.h"
#include <SFML/Graphics.hpp>
#include <memory>

class PotionSprite : public Potion {
private:
    sf::Texture texture;
    std::unique_ptr<sf::Sprite> sprite;

public:
    PotionSprite(int x, int y);
    void draw(sf::RenderWindow& window, int tileSize) override;
};