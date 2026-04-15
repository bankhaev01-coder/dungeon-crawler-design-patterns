#pragma once
#include <memory>
#include "Unit.h"

class UnitFactory {
public:
    virtual std::unique_ptr<Unit> createUnit(int x, int y) = 0;
    virtual ~UnitFactory() = default;
};

class HeroFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(int x, int y) override;
};

class EnemyFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(int x, int y) override;
};

class PotionFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(int x, int y) override;
};