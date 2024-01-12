#pragma once
#include "Position.h"
#include <vector>
class Hitbox {
	protected:
		Position position;
		Position farRightPosition;
		char id;
		bool action;
	public:
		Hitbox(Position posi, Position farRightPosi, char idd, bool actionn);
		void switchAction();
		bool isAction();
		char getId();
		void updatePosition(Position posi, Position rposi);
		bool hitBoxCompare(Hitbox combareMe);
		int bottomRightX();
		int bottomRightY();
		int topLeftX();

		int topLeftY();

};