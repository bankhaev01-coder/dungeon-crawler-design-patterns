#pragma once
#include "IUnitState.h"

class AttackingState : public IUnitState {
    Unit* target;
public:
    AttackingState(Unit* t) : target(t) {}
    void handle(Unit* unit, Battlefield& field) override;
};