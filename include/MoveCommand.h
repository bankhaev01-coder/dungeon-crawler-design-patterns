#pragma once
#include "Command.h"
#include "Unit.h"

class Battlefield;

class MoveCommand : public Command {
    Unit* unit;
    int fromX, fromY, toX, toY;
    Battlefield& field;
public:
    MoveCommand(Unit* u, int dx, int dy, Battlefield& f);
    void execute() override;
    void undo() override;
};