#pragma once
#include "Entity.h"
#include <iostream>

class childMissile;

class Missile : public Entity {
protected:
	std::vector<childMissile> missiles;
	std::vector<int> toDestroy;
	int iterator = 0;
public:
    Missile(Position posi);
    void setPosition(Position posit);
    void print() override; 
    void tick(int input, GameLogic* game) override;
};