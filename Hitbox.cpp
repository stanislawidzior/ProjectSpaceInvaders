#include "Hitbox.h"

Hitbox::Hitbox(Position posi = Position(0,0), Position farRightPosi = Position(0,0), char idd =' ', bool actionn = false): position(posi), farRightPosition(farRightPosi), id(idd), action(actionn) {
}
bool Hitbox::isAction() {
	return action;
}
char Hitbox::getId() {
	return id;
}
void Hitbox::updatePosition(Position posi, Position rposi) {
	position = posi;
	farRightPosition = rposi;
}
int Hitbox::bottomRightX() {
	return farRightPosition.getX();
}
int Hitbox::bottomRightY() {
	return farRightPosition.getY();
}
int Hitbox::topLeftX() {
	return position.getX();
}
int Hitbox::topLeftY() {
	return position.getY();
}
bool Hitbox::hitBoxCompare(Hitbox compareMe) {
	if (compareMe.bottomRightX() < topLeftX() || bottomRightX() < compareMe.topLeftX()) {
		return false;
	}

	if (compareMe.bottomRightY() < topLeftY() || bottomRightY() < compareMe.topLeftY()) {
		return false;
	}

	return true;
}
