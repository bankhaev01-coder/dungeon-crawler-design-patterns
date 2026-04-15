#pragma once
#include "UnitFactory.h"

class EnemySpriteFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(int x, int y) override;
};