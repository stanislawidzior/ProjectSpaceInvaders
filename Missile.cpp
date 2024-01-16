#include "Missile.h"
#include <ncursesw/curses.h>
#include "childMissile.h"

Missile::Missile(Position posi) : Entity(posi, "Missile") {
	id = 'm';
	hitbox = Hitbox(position, position, id, false);
}
void spawnMissiles(Position posi) {
}

void Missile::setPosition(Position posit) {

}
void Missile::tick(int input, GameLogic* game) {
	iterator++;
	if(iterator>300) iterator = 1;
	for(int i = 0; i < missiles.size(); i++){
		missiles.at(i).tick(i, game);	
	}
	std::vector<Hitbox> activatedHitbox = game->findAction();
	int size = activatedHitbox.size();
	for(int i = 0; i < size; i++) {
		if(activatedHitbox.at(i).getId() == 'p') {
			missiles.emplace_back(activatedHitbox.at(i).topMid(), 'm', iterator, 1);
		} else if (activatedHitbox.at(i).getId() == 'e'){
							move(22,15);
			addstr("missile wie ze  przeciwnik strzelil");
			missiles.emplace_back(activatedHitbox.at(i).bottomMid(), 'm', iterator, -1);
		}
	}
	for(int i = 0; i < missiles.size(); i++){
	
		if(missiles.at(i).destroyMe()){
			toDestroy.push_back(i);
			
		}
	}
	for(int i = 0; i<toDestroy.size(); i++){
		missiles.erase(missiles.begin() + toDestroy.at(i));
	}
	toDestroy.clear();
	for(int i = 0; i<missiles.size(); i++){
		missiles.at(i).tick(i, game);
		missiles.at(i).print();
	}
	
	toDestroy.clear();
}
void Missile::print() {
	move(position.getY(), position.getX());
	addch('*');
}
