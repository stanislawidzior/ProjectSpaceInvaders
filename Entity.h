#pragma once
#include "Position.h"
#include <iostream>
#include "GameLogic.h"

class Entity {
	protected:
		Position position;
		Position barrelPos;
		std::string fileName;
		Position farRightPosition;
	public:
		Entity(Position posi, const std::string& fileName);
		Position& getPosition();
		Position& getFarRightPosition();
		Position getBarrelPosition() const;
		virtual void tick(int input, GameLogic* game);
		virtual void print();
		virtual void checkCollision(std::vector<Position> map);
};