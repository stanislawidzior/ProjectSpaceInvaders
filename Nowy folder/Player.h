#pragma once
#include "Entity.h"
class Player : public Entity {
	public:
		Player(Position posi);
		void tick(int input, GameLogic* game) override;
		void checkCollision(std::vector<Position> map) override;

	};