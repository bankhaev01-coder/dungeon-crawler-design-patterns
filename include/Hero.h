#pragma once
#include "Unit.h"

class Hero : public Unit {
public:
    Hero(int startX, int startY);
    char getSymbol() const override;
};