#include "AttackingState.h"
#include "Unit.h"
#include "Battlefield.h"
#include "IdleState.h"

void AttackingState::handle(Unit* unit, Battlefield& field) {
    if (target && target->isAlive()) {
        target->takeDamage(unit->getAttack());
    }
    unit->setState(std::make_unique<IdleState>());
}