#include "AttackCommand.h"

AttackCommand::AttackCommand(Unit* a, Unit* t, int dmg)
    : attacker(a), target(t), damage(dmg) {}

void AttackCommand::execute() {
    if (target && target->isAlive()) {
        target->takeDamage(damage);
    }
}

void AttackCommand::undo() {
    if (target) {
        target->takeDamage(-damage);
    }
}