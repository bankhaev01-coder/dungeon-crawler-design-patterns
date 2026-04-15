#include "EnemySpriteFactory.h"
#include "EnemySprite.h"

std::unique_ptr<Unit> EnemySpriteFactory::createUnit(int x, int y) {
    return std::make_unique<EnemySprite>(x, y);
}