#pragma once
#include "UnitFactory.h"

class PotionSpriteFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(int x, int y) override;
};