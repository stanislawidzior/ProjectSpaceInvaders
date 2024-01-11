#include "Player.h"
#include <ncursesw/curses.h>

	Player::Player(Position posi) : Entity(posi, "assets/player.txt") {
		}

	void Player::tick(int input, GameLogic* game){
	move(15,15);
	addstr("gownogowno");
	switch(input) {
				case 32:
					game->switchShooting();
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
			checkCollision(game->getHitmap());
			print();
	}
	
	void Player::checkCollision(std::vector<Position> map){
			
		}


