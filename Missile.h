#pragma once
#include "Entity.h"

class Missile : public Entity {
public:
    Missile(Position posi);
    void setPosition(Position posit);
    void print() override; 
    void tick(int input, GameLogic* game) override;
};