#pragma once
#include <vector>
#include <memory>
#include "Unit.h"
#include "Hero.h"
#include "Enemy.h"
#include "TileMap.h"

class Battlefield {
private:
    std::unique_ptr<TileMap> tileMap;
    std::vector<std::unique_ptr<Unit>> units;

public:
    Battlefield();

    // Загрузка уровня из данных тайлов
    bool loadLevel(const std::string& tilesetPath, const std::vector<int>& tiles,
                   int width, int height, int tileSize = 32);

    void generateLevel();

    // Управление юнитами
    void addUnit(std::unique_ptr<Unit> unit);
    Unit* getUnitAt(int x, int y);
    void removeDeadUnits();
    bool isCellFree(int x, int y) const;
    void moveUnit(Unit* unit, int newX, int newY);

    void draw(sf::RenderWindow& window);

    // Доступ к герою и врагам
    Hero* getHero();
    const Hero* getHero() const;
    std::vector<Enemy*> getEnemies();

    bool heroAlive() const;
    bool enemiesAlive() const;

    // Размеры поля (получаем из tileMap)
    int getWidth() const { return tileMap ? tileMap->getWidth() : 0; }
    int getHeight() const { return tileMap ? tileMap->getHeight() : 0; }
};