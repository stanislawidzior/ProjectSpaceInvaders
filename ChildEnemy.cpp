#include "ChildEnemy.h"
#include <ncursesw/curses.h>

ChildEnemy::ChildEnemy(Position posi,char idd) : Enemies(posi){
	id = idd;
	hitbox = Hitbox(position, farRightPosition, id, action);
}
void ChildEnemy::setId(char idd){
}
void ChildEnemy::tick(int input, GameLogic* game){
	if(game->getMoveDelay() == 0){	
		position.incX(input*1);
		farRightPosition.incX(input*1);
		hitbox.updatePosition(position,farRightPosition);
	}
	game->updateHitmap(hitbox);
	print();
}