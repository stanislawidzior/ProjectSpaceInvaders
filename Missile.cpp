#include "Missile.h"
#include <ncursesw/curses.h>

Missile::Missile(Position posi) : Entity(posi, "Missile") {}

void Missile::setPosition(Position posit) {
    position = posit;
}
void Missile::tick(int input, GameLogic* game){
}
void Missile::print() {
    move(position.getY(), position.getX());
    addch('*');
}