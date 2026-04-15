#pragma once
#include "Unit.h"

class Hero;

class Potion : public Unit {
public:
    Potion(int startX, int startY);
    void use(Hero* hero);
    char getSymbol() const override;
};