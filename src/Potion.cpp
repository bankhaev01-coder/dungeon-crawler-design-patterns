#include "Potion.h"
#include "Hero.h"

Potion::Potion(int startX, int startY)
    : Unit("Potion", 1, 0, startX, startY) {}

void Potion::use(Hero* hero) {
    hero->takeDamage(-20); // восстанавливает 20 HP
    health = 0;
}

char Potion::getSymbol() const {
    return 'P';
}