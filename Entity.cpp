#include "Entity.h"
#include "Position.h"
#include <iostream>
#include <fstream>
#include <ncursesw/curses.h>

Entity::Entity(Position posi, const std::string& fileName):position(posi), fileName(fileName), farRightPosition(posi), id('n'), action(false), hitbox(posi,posi,'n', false) {
}
Position& Entity::getPosition() {
	return position;
}
Position& Entity::getFarRightPosition() {
	return farRightPosition;
}
void Entity::tick(int input, GameLogic* game) {
}
void Entity::checkCollision(std::vector<Position> map){
}
void Entity::print() {
	std::ifstream sprite(fileName);
	if (!sprite.is_open()) {
		std::cerr << "Error missing file \"" << fileName << "\"" << std::endl;
		return;
	}

	std::string line;
	int yOffset = 0;
	while (std::getline(sprite, line)) {
		for (int i = 0; i < line.size(); i++) {
			move(position.getY() + yOffset, position.getX() + i);
			if (i == line.size() / 2 && yOffset == 0) {
			}
			addch(line.at(i));
		}
		yOffset++;
	}
	sprite.close();
}
Hitbox Entity::getHitbox(){
	return hitbox;
};
