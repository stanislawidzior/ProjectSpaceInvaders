#include "Entity.h"
#include "Position.h"
#include <iostream>
#include <fstream>
#include <ncursesw/curses.h>

Entity::Entity(Position posi, const std::string& fileName):position(posi), barrelPos(0,0), fileName(fileName), farRightPosition(posi) {
}
Position& Entity::getPosition() {
	return position;
}
Position& Entity::getFarRightPosition() {
	return farRightPosition;
}
Position Entity::getBarrelPosition() const {
	return barrelPos;
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
				barrelPos.incX(position.getX() + i);
				barrelPos.incY(position.getY() + yOffset + 2);
			}
			addch(line.at(i));
		}
		yOffset++;
	}
	sprite.close();
}
