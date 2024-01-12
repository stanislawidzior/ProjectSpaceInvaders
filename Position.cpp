#include "Position.h"

Position::Position(int x, int y): X(x), Y(y) {}
void Position::incX(int j) {
	X+=j;
}
void Position::incY(int j) {
	Y-=j;
}
int Position::getY() const {
	return Y;
}
int	Position::getX() const {
	return X;
}

