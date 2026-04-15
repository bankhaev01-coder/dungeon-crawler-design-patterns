#pragma once
#include "IBehaviorStrategy.h"
class DefensiveStrategy : public IBehaviorStrategy {
public:
    void execute(Enemy* enemy, Battlefield& field) override;
};