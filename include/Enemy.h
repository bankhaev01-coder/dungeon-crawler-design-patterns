#pragma once
#include "Unit.h"
#include "IBehaviorStrategy.h"
#include <memory>

class Enemy : public Unit {
    std::unique_ptr<IBehaviorStrategy> strategy;
public:
    Enemy(int startX, int startY);
    void setStrategy(std::unique_ptr<IBehaviorStrategy> newStrategy);
    void act(Battlefield& field);
    char getSymbol() const override;
};