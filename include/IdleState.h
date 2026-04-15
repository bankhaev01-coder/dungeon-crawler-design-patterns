#pragma once
#include "IUnitState.h"

class IdleState : public IUnitState {
public:
    void handle(Unit* unit, Battlefield& field) override;
};