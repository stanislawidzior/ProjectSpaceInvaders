#pragma once
#include "Entity.h"
#include "Hitbox.h"
class Player : public Entity {
	int health = 3;
	bool action = false;
	public:
		Player(Position posi);
		void tick(int input, GameLogic* game) override;
		void checkCollision(char id);

	};