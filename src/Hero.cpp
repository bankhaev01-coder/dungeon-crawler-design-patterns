#include "Hero.h"

Hero::Hero(int startX, int startY) 
    : Unit("Hero", 50, 15, startX, startY) {}

char Hero::getSymbol() const {
    return '@';
}