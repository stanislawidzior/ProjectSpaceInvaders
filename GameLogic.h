#pragma once
#include <vector>
#include <iostream>
#include "Position.h"
#include "Hitbox.h"
class GameLogic {
	protected:
		int shootingDelay;
		int enemyMoveDelay ;
		std::vector<Hitbox> hitmap;
		bool playing = true;
		int score;
		int width;
		int height;
		int numberOfOponents = 8;
		std::vector<int> destroy;
	public:
		GameLogic(int shootdel, int emdel, int scor);
		void incScore(int x);
		int getWidth();
		int getHeight();
		void endGame();
		int getScore();
		int getNumOfOponents();
		void setShootingDelay(int x);
		int getShootingDelay();
		int getMoveDelay();
		void updateHitmap(Hitbox &box, bool replace);
		char checkOverlapping(char id, int countt);
		void printHitmap();
		void tick();
		std::vector<Hitbox> findAction();
		void destroythem();
		void getUpdate(Hitbox& box);
		void printUi();
		bool isplaying();
};