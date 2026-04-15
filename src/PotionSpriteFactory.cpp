#include "PotionSpriteFactory.h"
#include "PotionSprite.h"

std::unique_ptr<Unit> PotionSpriteFactory::createUnit(int x, int y) {
    return std::make_unique<PotionSprite>(x, y);
}