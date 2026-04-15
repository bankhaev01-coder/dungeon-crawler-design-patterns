#pragma once
#include "Hero.h"
#include <SFML/Graphics.hpp>
#include <memory>

class HeroSprite : public Hero {
private:
    sf::Texture texture;
    std::unique_ptr<sf::Sprite> sprite;

public:
    HeroSprite(int x, int y);
    void draw(sf::RenderWindow& window, int tileSize) override;
};