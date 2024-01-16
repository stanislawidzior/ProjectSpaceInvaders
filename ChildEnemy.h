#pragma once
#include "Enemies.h"
class ChildEnemy : public Enemies{
protected:
	bool hit = false;
	int count = 0;
	bool justrespawned = true;
	bool action = false;
	
public:
	ChildEnemy(Position posi,char idd, int coun);
 void tick(int input, GameLogic* game) override;
 void setId(char idd);
 void getHitbox();
 bool isHit();
 void checkCollision(char id);
 void switchHit();
 void switchAction();
};

