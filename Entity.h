#pragma once
#include "Position.h"
#include <iostream>
#include "GameLogic.h"
#include "Hitbox.h"

class Entity {
	protected:
		Position position;
		std::string fileName;
		Position farRightPosition;
		Hitbox hitbox;
		char id;
		bool action;
	public:
		Entity(Position posi, const std::string& fileName);
		Position& getPosition();
		Position& getFarRightPosition();
		virtual void tick(int input, GameLogic* game);
		virtual void print();
		virtual void checkCollision(std::vector<Position> map);
		Hitbox getHitbox();
};