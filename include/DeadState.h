#pragma once
#include "IUnitState.h"

class DeadState : public IUnitState {
public:
    void handle(Unit* unit, Battlefield& field) override;
};