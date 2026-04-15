#include "Unit.h"
#include "IdleState.h"

Unit::Unit(const std::string& n, int hp, int atk, int startX, int startY)
    : name(n), health(hp), maxHealth(hp), attackPower(atk), x(startX), y(startY) {
    state = std::make_unique<IdleState>();
}

void Unit::setState(std::unique_ptr<IUnitState> newState) {
    state = std::move(newState);
}

void Unit::handleState(Battlefield& field) {
    if (state) state->handle(this, field);
}

void Unit::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
}

bool Unit::isAlive() const {
    return health > 0;
}

void Unit::move(int dx, int dy) {
    x += dx;
    y += dy;
}