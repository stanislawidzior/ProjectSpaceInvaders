#include "Player.h"
#include <ncursesw/curses.h>

	Player::Player(Position posi) : Entity(posi, "assets/player.txt"){
		farRightPosition = Position(posi.getX() + 13, posi.getY() + 6);
        id = 'p';
		hitbox = Hitbox(position, farRightPosition, id, false);
        
		}

		void Player::checkCollision(char idcoliding){
			if(idcoliding = 'n')
			return;
			if(idcoliding = 'm')
			health--;
		}

	void Player::tick(int input, GameLogic* game){
	move(15,15);
	//addstr("gownogowno");
	switch(input) {
				case 32:
					
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
			game->updateHitmap(hitbox);
			checkCollision(game->checkOverlapping(id));
			print();
			//game->printHitmap();
	}
	


