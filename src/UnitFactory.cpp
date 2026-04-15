#include "UnitFactory.h"
#include "Hero.h"
#include "Enemy.h"
#include "Potion.h"

std::unique_ptr<Unit> HeroFactory::createUnit(int x, int y) {
    return std::make_unique<Hero>(x, y);
}

std::unique_ptr<Unit> EnemyFactory::createUnit(int x, int y) {
    return std::make_unique<Enemy>(x, y);
}

std::unique_ptr<Unit> PotionFactory::createUnit(int x, int y) {
    return std::make_unique<Potion>(x, y);
}