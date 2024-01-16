#include "ChildEnemy.h"
#include <ncursesw/curses.h>


ChildEnemy::ChildEnemy(Position posi,char idd, int coun) : Enemies(posi){
	id = idd;
	hitbox = Hitbox(position, farRightPosition, id, action);
	hitbox.setCount(coun);
}
void ChildEnemy::setId(char idd){
}
void ChildEnemy::checkCollision(char idcoliding){
	if(idcoliding = 'n')
	return;
	else if (idcoliding = 'm'){

		hit = true;
	}
		
}
void ChildEnemy::tick(int input, GameLogic* game){

	if(!justrespawned)game->getUpdate(hitbox);
	else justrespawned = false;
	if(action){
		hitbox.switchAction();
	}
	if(game->getShootingDelay()!=0 && hitbox.isAction()){
			move(21,15);
			addstr("przeciwnik mowi juz nie strzela");
		action = false;
		hitbox.switchAction();
	}
	if(hitbox.isColiding()){
		checkCollision(hitbox.colidingId());
		move(19,16);
		addch(hitbox.colidingId());
		hitbox.switchColiding();
		game->incScore(1);
		hitbox.switchStatus();
		hit = true;
		game->updateHitmap(hitbox,true);
		return;
	}
	if(game->getMoveDelay() == 0){	
			move(4,6);
	addstr(std::to_string(input).c_str());
		position.incX(input*1);
		farRightPosition.incX(input*1);
		hitbox.updatePosition(position,farRightPosition);
	}

		game->updateHitmap(hitbox,true);
		print();
}

bool ChildEnemy::isHit(){
	return hit;
}
void ChildEnemy::switchHit(){
	hit = !hit;
	hitbox.switchStatus();
}
void ChildEnemy::switchAction(){
	action = !action;
	
}

