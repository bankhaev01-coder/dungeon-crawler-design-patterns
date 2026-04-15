#include "MoveCommand.h"
#include "Battlefield.h"

MoveCommand::MoveCommand(Unit* u, int dx, int dy, Battlefield& f)
    : unit(u), fromX(u->getX()), fromY(u->getY()),
      toX(fromX + dx), toY(fromY + dy), field(f) {}

void MoveCommand::execute() {
    if (field.isCellFree(toX, toY)) {
        field.moveUnit(unit, toX, toY);
    }
}

void MoveCommand::undo() {
    field.moveUnit(unit, fromX, fromY);
}