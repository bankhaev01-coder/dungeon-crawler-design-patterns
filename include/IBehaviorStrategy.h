#pragma once
class Enemy;
class Battlefield;

class IBehaviorStrategy {
public:
    virtual void execute(Enemy* enemy, Battlefield& field) = 0;
    virtual ~IBehaviorStrategy() = default;
};