#include "Hitbox.h"

Hitbox::Hitbox(Position posi = Position(0,0), Position farRightPosi = Position(0,0), char idd =' ', bool actionn = false): position(posi), farRightPosition(farRightPosi), id(idd), action(actionn) {
}
bool Hitbox::isAction() {
	return action;
}
char Hitbox::getId() {
	return id;
}
void Hitbox::setCount(int i){
	count = i;
}
		int Hitbox::getCount(){
			return count;
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
Position Hitbox::topMid () {
	return Position(((bottomRightX() - topLeftX()) / 2) + topLeftX(), topLeftY() - 1);
}
Position Hitbox::bottomMid () {
	return Position(((bottomRightX() - topLeftX()) / 2) + topLeftX(), bottomRightY() + 1);
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
char Hitbox::colidingId() {
	return colidingid;
}
void Hitbox::setColidingId(char idd) {
	colidingid = idd;
}
void Hitbox::switchColiding() {
	coliding = !coliding;
}
bool Hitbox::isColiding() {
	return coliding;
}
void Hitbox::switchAction(){
	action = !action;
}
void	Hitbox::destroyMe(){
	destroy = true;
	}
	bool Hitbox::wantsDestroyed(){
		return destroy;
	}
	
			void Hitbox::switchStatus(){
				isActive = !isActive;
			}
		bool Hitbox::getStatus(){
			return isActive;
		}
