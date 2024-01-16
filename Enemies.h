#pragma once
#include "Entity.h"
#include "Hitbox.h"
class ChildEnemy;
class Enemies : public Entity {
	protected:
		int direction = -1;
		int iterator = 0;
		std::vector<ChildEnemy> childEnemies;
		bool spawned = false;
	public:
		Enemies(Position posi);
		void changeDirection();
		void tick(int input, GameLogic* game) override;
		void spawnChilds(int amount);
		bool CheckIfRespawn();
};