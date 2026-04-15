#include "MovingState.h"
#include "Unit.h"
#include "Battlefield.h"
#include "IdleState.h"

void MovingState::handle(Unit* unit, Battlefield& field) {
    if (unit->getX() == targetX && unit->getY() == targetY) {
        unit->setState(std::make_unique<IdleState>());
        return;
    }
    int dx = targetX - unit->getX();
    int dy = targetY - unit->getY();
    int stepX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
    int stepY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;
    int newX = unit->getX() + stepX;
    int newY = unit->getY() + stepY;
    if (field.isCellFree(newX, newY)) {
        field.moveUnit(unit, newX, newY);
    } else {
        unit->setState(std::make_unique<IdleState>());
    }
}