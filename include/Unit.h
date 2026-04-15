#pragma once
#include <string>
#include <memory>
#include "IUnitState.h"
#include <SFML/Graphics.hpp>

class Battlefield;

class Unit {
protected:
    std::string name;
    int health;
    int maxHealth;
    int attackPower;
    int x, y;
    std::unique_ptr<IUnitState> state;

public:
    Unit(const std::string& n, int hp, int atk, int startX, int startY);
    virtual ~Unit() = default;

    virtual void draw(sf::RenderWindow& window, int tileSize) {}

    virtual char getSymbol() const = 0;

    void setState(std::unique_ptr<IUnitState> newState);
    void handleState(Battlefield& field);

    void takeDamage(int dmg);
    bool isAlive() const;
    void move(int dx, int dy);

    int getX() const { return x; }
    int getY() const { return y; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getAttack() const { return attackPower; }
    std::string getName() const { return name; }
};