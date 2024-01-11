#pragma once
#include <vector>
#include "Position.h"
class GameLogic{
protected:
	int shootingDelay;
	int enemyMoveDelay ;
	std::vector<Position> hitmap;
	std::vector<char> id;
	bool shooting = false;
	bool playing = true;
	int score;
	int health = 3;
	int width;
	int height;
	int numberOfOponents = 6;
public:
	GameLogic(int shootdel, int emdel, int scor, int helt);
	void incScore(int x);
	int getWidth();
	int getHeight();
	void endGame();
	int getScore();
	int getNumOfOponents();
	void setShootingDelay(int x);
	int getMoveDelay();
	std::vector<Position> getHitmap();
	void updateHitmap(std::vector<Position> updatedHitmap, std::vector<char> id);
	void switchShooting();
	void tick();
};