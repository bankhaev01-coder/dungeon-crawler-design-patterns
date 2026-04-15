#include "Enemy.h"
#include "AggressiveStrategy.h"

Enemy::Enemy(int startX, int startY)
    : Unit("Enemy", 30, 10, startX, startY) {
    strategy = std::make_unique<AggressiveStrategy>();
}

void Enemy::setStrategy(std::unique_ptr<IBehaviorStrategy> newStrategy) {
    strategy = std::move(newStrategy);
}

void Enemy::act(Battlefield& field) {
    if (strategy) strategy->execute(this, field);
}

char Enemy::getSymbol() const {
    return 'E';
}