#pragma once
#include "Hitbox.h"
#include "Missile.h"

class childMissile : public Missile{
	bool destroy = false;
	int direction = 1;
	public:
		childMissile(Position posi, char id,int coun, int direction);
		void tick(int input, GameLogic* game);
		bool destroyMe();
};
