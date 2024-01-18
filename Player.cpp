#include "Player.h"
#include <ncursesw/curses.h>

	Player::Player(Position posi) : Entity(posi, "assets/player.txt"){
		farRightPosition = Position(posi.getX() + 13, posi.getY() + 6);
        id = 'p';
		hitbox = Hitbox(position, farRightPosition, id, false);
        
		}

		void Player::checkCollision(char idcoliding){
			if(idcoliding == 'n')
			return;
			else if(idcoliding == 'm'){
				health--;
			}
			
		}
	void Player::printHealth(int width){
		std::string word;
		for(int i = 0; i < health; i++){
		  	word += "<3 ";
		}
		move(1,width - 10);
		addstr(word.c_str());
	}
	void Player::tick(int input, GameLogic* game){
	if(hitbox.isAction())action = false;
	game->getUpdate(hitbox);
	if(hitbox.isAction() == true && action == false){
		hitbox.switchAction();
	}
					if(hitbox.isColiding()){
				checkCollision(hitbox.colidingId());
				if(health == 0) game->endGame();
				hitbox.switchColiding();
				}
	switch(input) {

				case 32:
					hitbox.switchAction();
					action = true;
					break;
				case KEY_LEFT:
					if(position.getX() > 0)
						position.incX(-1);
						farRightPosition.incX(-1);
					break;
				case KEY_RIGHT:
					if(position.getX()< game->getWidth()-14)
						position.incX(1);
						farRightPosition.incX(1);
					break;
				case 'q':
				case 'Q':
					// wychodzimy z programu
					game->endGame();
					break;
				default:
					// zmieniamy wyświetlany kursor
					break;
			};
			hitbox.updatePosition(position,farRightPosition);
			game->updateHitmap(hitbox, true);
			print();
			printHealth(game->getWidth());
			move(2,game->getWidth() - 6);
			//addstr(std::to_string(health).c_str());
	}
	


