#include "GameLogic.h"
#include <ncursesw/curses.h>


	GameLogic::GameLogic(int shootdel, int emdel, int scor, int helt) : shootingDelay(shootdel), enemyMoveDelay(emdel), score(scor), health(helt){
		getmaxyx(stdscr, height, width);
	}
	int GameLogic::getNumOfOponents(){
		return numberOfOponents;
	}
		int GameLogic::getWidth(){
			return width;
		}
	int GameLogic::getHeight(){
			return height;
		}
		void GameLogic::endGame(){ 
		playing = false;
		}
	void 	GameLogic::incScore(int x){
		score+=x;
	}
	int 	GameLogic::getScore(){
		return score;
	}
	void 	GameLogic::setShootingDelay(int x){
		shootingDelay = x;
	}
	int GameLogic::getMoveDelay (){
		return enemyMoveDelay;
	}
	std::vector<Position> GameLogic::getHitmap(){
		return hitmap;
	}
	void GameLogic::switchShooting(){
		shooting = !shooting;
	}
	void 	GameLogic::updateHitmap(std::vector<Position> updatedHitmap, std::vector<char> id){
		hitmap = updatedHitmap;
		
	}
	void GameLogic::tick(){
		enemyMoveDelay--;
		if(enemyMoveDelay < 0) enemyMoveDelay = 5;
	}
	