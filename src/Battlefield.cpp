#include "Battlefield.h"
#include "UnitFactory.h"
#include "Hero.h"
#include "Enemy.h"
#include <iostream>
#include <algorithm>
#include "Potion.h"     
#include <cstdlib>

Battlefield::Battlefield() {
    tileMap = std::make_unique<TileMap>();
}

void Battlefield::generateLevel() {
    HeroFactory hf;
    EnemyFactory ef;
    PotionFactory pf;

    addUnit(hf.createUnit(2, 2));               // герой
    addUnit(ef.createUnit(5, 5));               // враг 1
    addUnit(ef.createUnit(7, 3));               // враг 2
    addUnit(pf.createUnit(3, 6));               // зелье
    addUnit(pf.createUnit(8, 8));               // зелье
}

void Battlefield::addUnit(std::unique_ptr<Unit> unit) {
    units.push_back(std::move(unit));
}

Unit* Battlefield::getUnitAt(int x, int y) {
    for (auto& u : units) {
        if (u->getX() == x && u->getY() == y && u->isAlive())
            return u.get();
    }
    return nullptr;
}

bool Battlefield::isCellFree(int x, int y) const {
    if (tileMap->isSolid(x, y)) return false;
    for (const auto& u : units) {
        if (u->getX() == x && u->getY() == y && u->isAlive())
            return false;
    }
    return true;
}

void Battlefield::draw(sf::RenderWindow& window) {
    if (tileMap) window.draw(*tileMap);
    int tileSize = 32;
    for (auto& unit : units) {
        if (unit->isAlive())
            unit->draw(window, tileSize);
    }
}

void Battlefield::moveUnit(Unit* unit, int newX, int newY) {
    // Проверка на зелье/врага при движении
    Unit* other = getUnitAt(newX, newY);
    if (auto* hero = dynamic_cast<Hero*>(unit)) {
        if (auto* potion = dynamic_cast<Potion*>(other)) {
            potion->use(hero);
        }
    }
    unit->move(newX - unit->getX(), newY - unit->getY());
}

void Battlefield::removeDeadUnits() {
    units.erase(std::remove_if(units.begin(), units.end(),
        [](const std::unique_ptr<Unit>& u) { return !u->isAlive(); }),
        units.end());
}


Hero* Battlefield::getHero() {
    for (auto& u : units) {
        if (auto* h = dynamic_cast<Hero*>(u.get()))
            return h;
    }
    return nullptr;
}

const Hero* Battlefield::getHero() const {
    for (const auto& u : units) {
        if (const auto* h = dynamic_cast<const Hero*>(u.get()))
            if (h->isAlive()) return h;
    }
    return nullptr;
}

std::vector<Enemy*> Battlefield::getEnemies() {
    std::vector<Enemy*> result;
    for (auto& u : units) {
        if (auto* e = dynamic_cast<Enemy*>(u.get()))
            result.push_back(e);
    }
    return result;
}

bool Battlefield::heroAlive() const {
    for (const auto& u : units) {
        if (dynamic_cast<Hero*>(u.get()) && u->isAlive())
            return true;
    }
    return false;
}

bool Battlefield::enemiesAlive() const {
    for (const auto& u : units) {
        if (dynamic_cast<Enemy*>(u.get()) && u->isAlive())
            return true;
    }
    return false;
}

bool Battlefield::loadLevel(const std::string& tilesetPath, const std::vector<int>& tiles,
                            int width, int height, int tileSize) {
    tileMap = std::make_unique<TileMap>();
    return tileMap->load(tilesetPath, tiles, width, height, tileSize);
}