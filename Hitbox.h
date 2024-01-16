#pragma once
#include "Position.h"
#include <vector>
class Hitbox {
	protected:
		Position position;
		Position farRightPosition;
		char id;
		int count = 0;
		bool action = false;
		bool coliding = false;
		char colidingid = 'n';
		bool destroy = false;
		bool isActive = true;
	public:
		Hitbox(Position posi, Position farRightPosi, char idd, bool actionn);
		void switchAction();
		bool isAction();
		void switchStatus();
		bool getStatus();
		char getId();
		void setCount(int i);
		int getCount();
		void updatePosition(Position posi, Position rposi);
		bool hitBoxCompare(Hitbox combareMe);
		int bottomRightX();
		int bottomRightY();
		int topLeftX();
		void switchColiding();
		bool isColiding();
		char colidingId();
		void setColidingId(char idd);
		int topLeftY();
	Position topMid ();
	Position bottomMid ();
	void destroyMe();
	bool wantsDestroyed();
	
};