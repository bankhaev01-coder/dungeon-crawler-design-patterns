#pragma once
class Unit;
class Battlefield;

class IUnitState {
public:
    virtual void handle(Unit* unit, Battlefield& field) = 0;
    virtual ~IUnitState() = default;
};