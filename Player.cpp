#include "Player.h"
#include <ncursesw/curses.h>

	Player::Player(Position posi) : Entity(posi, "assets/player.txt"), hitbox(posi,posi,' ', 0) {
		farRightPosition = Position(posi.getX() + 13, posi.getY() + 6);
        hitbox = Hitbox(position, farRightPosition, id, false);
		}

		void Player::checkCollision(char idcol){
			if(idcol = 'n')
			return;
			if(idcol = 'm')
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
					break;
				case KEY_RIGHT:
					if(position.getX()< game->getWidth()-14)
						position.incX(1);
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
			game->updateHitmap({position, farRightPosition, id, false});
			checkCollision(game->checkOverlapping(id));
			print();
			game->printHitmap();
	}
	


