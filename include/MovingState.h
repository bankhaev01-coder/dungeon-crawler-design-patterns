#pragma once
#include "IUnitState.h"

class MovingState : public IUnitState {
    int targetX, targetY;
public:
    MovingState(int tx, int ty) : targetX(tx), targetY(ty) {}
    void handle(Unit* unit, Battlefield& field) override;
};