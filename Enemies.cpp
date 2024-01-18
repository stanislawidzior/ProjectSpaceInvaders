#include "Enemies.h"
#include <ncursesw/curses.h>
#include "ChildEnemy.h"
#include <stdlib.h> 
#include <time.h> 
Enemies::Enemies(Position posi) : Entity(posi, "assets/enemies.txt") {
	getFarRightPosition() = Position(posi.getX() + 6, posi.getY() + 2);
	id = 'E';
	hitbox = Hitbox(posi, farRightPosition, id, false);
}
void Enemies::changeDirection() {
	direction = direction*(-1);
}
void Enemies::spawnChilds(int amount) {
	Position posi = farRightPosition;
	for(int i = 0; i < amount; i++) {
		posi.incX(11);
		childEnemies.emplace_back(posi,'e',i);
	}
	spawned = true;
}
bool Enemies::CheckIfRespawn(){
	for(int i = 0; i < childEnemies.size(); i++){
		if(!childEnemies.at(i).isHit())
		{
			return false;
		}
	}
	return true;
}

void Enemies::tick(int input, GameLogic* game) {
	iterator++;
	if(!spawned) {
		spawnChilds(game->getNumOfOponents());
	}
	


	if(childEnemies.at(0).getPosition().getX() <= 2 || childEnemies.at(childEnemies.size() - 1).getPosition().getX() >= game->getWidth() - 6  ) {
		if(game->getMoveDelay() == 0)
		changeDirection();

	}

	if(CheckIfRespawn()){
		for(int i = 0; i < childEnemies.size(); i++){
			childEnemies.clear();
			spawnChilds(game->getNumOfOponents());	
			game->incShootDelay(-1);
		}
	}
	if(game->getShootingDelay() == 0){
			srand(time(NULL));
			childEnemies.at(rand() % childEnemies.size()).switchAction();
	}
	for(int i = 0; i < childEnemies.size(); i++){
		childEnemies.at(i).tick(direction, game);
	
	}
		
}