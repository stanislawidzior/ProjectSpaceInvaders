#include "childMissile.h"
#include <ncursesw/curses.h>

childMissile::childMissile(Position posi, char idd,int coun, int directio) : Missile(posi) {
	id = idd;
	hitbox = Hitbox(posi, posi, id, false);
	hitbox.setCount(coun);
	direction = directio;
}
void childMissile::tick(int input, GameLogic* game){
	game->getUpdate(hitbox);
	if( position.getY() <= 0 || position.getY() > game->getHeight()){
		destroy = true;
		hitbox.destroyMe();
			}
	if(hitbox.isColiding()){
		destroy = true;
		hitbox.destroyMe();
	}
	else{
	position.incY(1*direction);
	farRightPosition.incY(1*direction);
	hitbox.updatePosition(position,farRightPosition);
}
	game->updateHitmap(hitbox, true);
	
}
bool childMissile::destroyMe(){
	return destroy;
}