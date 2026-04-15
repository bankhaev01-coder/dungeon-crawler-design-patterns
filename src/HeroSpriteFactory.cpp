#include "HeroSpriteFactory.h"
#include "HeroSprite.h"

std::unique_ptr<Unit> HeroSpriteFactory::createUnit(int x, int y) {
    return std::make_unique<HeroSprite>(x, y);
}