#include "AggressiveStrategy.h"
#include "Enemy.h"
#include "Battlefield.h"
#include "Hero.h"
#include <cmath>
#include "GameManager.h"

void AggressiveStrategy::execute(Enemy* enemy, Battlefield& field) {
    Hero* hero = field.getHero();
    if (!hero) return;

    int dx = hero->getX() - enemy->getX();
    int dy = hero->getY() - enemy->getY();

    // Если рядом — атаковать
    if (std::abs(dx) <= 1 && std::abs(dy) <= 1) {
        int dmg = enemy->getAttack();
        hero->takeDamage(dmg);
        GameManager::getInstance().notify("Enemy attacks Hero for " + std::to_string(dmg) + " damage!");
    }
    // Иначе двигаться к герою
    else {
        int stepX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
        int stepY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;
        int newX = enemy->getX() + stepX;
        int newY = enemy->getY() + stepY;
        if (field.isCellFree(newX, newY)) {
            field.moveUnit(enemy, newX, newY);
        }
    }
}