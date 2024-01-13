#pragma once
#include "Enemies.h"
class ChildEnemy : public Enemies{
public:
	ChildEnemy(Position posi,char idd);
 void tick(int input, GameLogic* game) override;
 void setId(char idd);
 void getHitbox();
};

