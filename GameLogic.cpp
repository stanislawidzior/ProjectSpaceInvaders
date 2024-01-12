#include "GameLogic.h"
#include <ncursesw/curses.h>


GameLogic::GameLogic(int shootdel, int emdel, int scor, int helt) : shootingDelay(shootdel), enemyMoveDelay(emdel), score(scor), health(helt) {
	getmaxyx(stdscr, height, width);
}
int GameLogic::getNumOfOponents() {
	return numberOfOponents;
}
int GameLogic::getWidth() {
	return width;
}
int GameLogic::getHeight() {
	return height;
}
void GameLogic::endGame() {
	playing = false;
}
void 	GameLogic::incScore(int x) {
	score+=x;
}
int 	GameLogic::getScore() {
	return score;
}
void 	GameLogic::setShootingDelay(int x) {
	shootingDelay = x;
}
int GameLogic::getMoveDelay () {
	return enemyMoveDelay;
}

void GameLogic::updateHitmap(Hitbox box) {
	bool found = false;
	for(int i  = 0; i < hitmap.size(); i++) {
		if(box.getId() == hitmap.at(i).getId()) {
			hitmap.at(i) = box;
			found = true;
		}
	}
	if(!found) hitmap.emplace_back(box);
}
char GameLogic::checkOverlapping(char id) {
	for(int i = 0; i <hitmap.size(); i++) {

		if(id == hitmap.at(i).getId()) {
			for(int j = 0; j < hitmap.size(); j++) {
				if(j!=i) {
					if(hitmap.at(i).hitBoxCompare(hitmap.at(j)))
						return hitmap.at(j).getId();
				}
			}
			return 'n';
		}
	}

}
void GameLogic::printHitmap() {
	for(int i = 0; i<hitmap.size(); i++) {
		move(15,15+i);
		addch(hitmap.at(i).getId());
	}
}
void GameLogic::tick() {
	enemyMoveDelay--;
	if(enemyMoveDelay < 0) enemyMoveDelay = 5;
}
