#include "GameLogic.h"
#include <ncursesw/curses.h>


GameLogic::GameLogic(int shootdel, int emdel, int scor) : shootingDelay(shootdel), enemyMoveDelay(emdel), score(scor) {
	getmaxyx(stdscr, height, width);
	shootingDelayStart = shootdel;
	enemyMoveDelayStart = emdel;
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

void GameLogic::updateHitmap(Hitbox &box, bool replace = true) {
	if(!replace){ 
	hitmap.emplace_back(box);
	return;
	}
	bool found = false;
	for(int i  = 0; i < hitmap.size(); i++) {
		if(box.getId() == hitmap.at(i).getId() && box.getCount() == hitmap.at(i).getCount()) {
			hitmap.at(i) = box;
			found = true;
			break;
		}
	}
	if(!found) hitmap.emplace_back(box);
}
void GameLogic::getUpdate(Hitbox& box) {
	for(int i  = 0; i < hitmap.size(); i++) {
		if(box.getId() == hitmap.at(i).getId() && box.getCount() == hitmap.at(i).getCount()) {
			box = hitmap.at(i);
			return;
		}
	}
	
}
char GameLogic::checkOverlapping(char id, int countt) {
    for(int i = 0; i < hitmap.size(); i++) {
    	if(hitmap.at(i).getStatus() == false)
    	continue;
        if(id == hitmap.at(i).getId() && countt == hitmap.at(i).getCount()) {
            for(int j = 0; j < hitmap.size(); j++) {
            	if(hitmap.at(j).getStatus() == false)
            	continue;
                if(j != i) {
                    if(hitmap.at(i).hitBoxCompare(hitmap.at(j))) {	
						hitmap.at(i).switchColiding();
                        hitmap.at(i).setColidingId(hitmap.at(j).getId());
                        hitmap.at(j).switchColiding();
                        hitmap.at(j).setColidingId(hitmap.at(i).getId());
                        return hitmap.at(j).getId();
                    }
                }
            }
            return 'n';
        }
    }
    return 'n';
}
void GameLogic::destroythem() {
    std::vector<Hitbox> tempHitmap;
    for (int i = 0; i < hitmap.size(); i++) {
        if (!hitmap.at(i).wantsDestroyed()) {
            tempHitmap.push_back(hitmap.at(i));
        }
    }
    hitmap = tempHitmap;
}
void GameLogic::printHitmap() {
	std::string word;
	for(int i = 0; i<hitmap.size(); i++) {
		if(hitmap.at(i).getStatus()){
		move(15-i,15);
		word = hitmap.at(i).getId() + std::to_string(hitmap.at(i).getCount()) + " ";
		addstr(word.c_str());
		}
		
	}
	
}
void GameLogic::printUi(){
	move (1,1);
	std::string word = " SCORE: " + std::to_string(score);
	addstr(word.c_str());
}
	int GameLogic::getShootingDelay(){
		return shootingDelay;
	}
void GameLogic::tick() {
	destroythem();
	enemyMoveDelay--;
	shootingDelay--;
	if(shootingDelay < 0) shootingDelay = shootingDelayStart;
	if(enemyMoveDelay < 0) enemyMoveDelay = enemyMoveDelayStart;
	checkOverlapping('p', 0);
	for(int i = 0; i < numberOfOponents; i++){
			checkOverlapping('e', i);
	}
	//printHitmap();
	printUi();

}
std::vector<Hitbox> GameLogic::findAction(){
	std::vector<Hitbox> activatedHitbox;
	for(int i = 0; i<hitmap.size(); i++){
		if(hitmap.at(i).isAction()){
		 	activatedHitbox.push_back(hitmap.at(i));
		}
		
	}
	return activatedHitbox;
}
bool GameLogic::isplaying(){
	return playing;
}
void GameLogic::incShootDelay(int i){
	if(shootingDelayStart > 1)shootingDelayStart += i;
	else return;
	
}

