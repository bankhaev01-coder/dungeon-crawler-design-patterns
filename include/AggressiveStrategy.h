#pragma once
#include "IBehaviorStrategy.h"
class AggressiveStrategy : public IBehaviorStrategy {
public:
    void execute(Enemy* enemy, Battlefield& field) override;
};