#include "Enemies.h"
#include <ncursesw/curses.h>
#include "ChildEnemy.h"
Enemies::Enemies(Position posi) : Entity(posi, "assets/enemies.txt"),hitbox(posi,posi,' ', 0) {
	getFarRightPosition() = Position(posi.getX() + 6, posi.getY() + 2);
	hitbox = Hitbox(position, farRightPosition, id, false);
}
void Enemies::changeDirection() {
	direction = direction*(-1);
}
void Enemies::spawnChilds() {
	Position posi = farRightPosition;
	for(int i = 0; i < 3; i++) {
		posi.incX(7);
		childEnemies.emplace_back(posi);
	}
	spawned = true;
}

void Enemies::tick(int input, GameLogic* game) {
	iterator++;
	if(!spawned) {
		spawnChilds();
	}
	if(iterator == 150) {
		changeDirection();

	}
	if(game->getMoveDelay() == 0) {
		position.incX(direction*1);
	}
	for(int i = 0; i < childEnemies.size(); i++)
		childEnemies.at(i).tick(direction, game);
}