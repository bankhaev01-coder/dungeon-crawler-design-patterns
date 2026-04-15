#pragma once
#include "Command.h"
#include "Unit.h"

class AttackCommand : public Command {
    Unit* attacker;
    Unit* target;
    int damage;
public:
    AttackCommand(Unit* a, Unit* t, int dmg);
    void execute() override;
    void undo() override;
};