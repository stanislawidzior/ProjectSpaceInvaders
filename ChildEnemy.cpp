#include "ChildEnemy.h"

ChildEnemy::ChildEnemy(Position posi) : Enemies(posi){
}
void ChildEnemy::setId(char idd){
	id = idd;
}
void ChildEnemy::tick(int input, GameLogic* game){
	if(game->getMoveDelay() == 0){	
		position.incX(input*1);
	}
	game->updateHitmap(hitbox);
	print();
}