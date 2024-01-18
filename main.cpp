#include <iostream>
#include <ncursesw/curses.h>
#include <fstream>
#ifdef _WIN32 // Sprawdzenie, czy kod jest kompilowany na Windows
#include <windows.h>
#endif
#include <unistd.h>
#include <vector>
#include "Position.h"
#include "Enemies.h"
#include "Entity.h"
#include "ChildEnemy.h"
#include "Missile.h"
#include "GameLogic.h"
#include "Player.h"

void ncurses_init_colors() {
	// więcej o kolorach tu https://www.linuxjournal.com/content/programming-color-ncurses

	// musimy ustawić jeśli będziemy używać kolorowania konsoli
	start_color();
	// i zdefiniować pary kolorów które będziemy używać
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
}

void ncurses_config() {
	//dla windows nalerzy zmienic konfigurację konsoli aby klikanie myszką działało
#ifdef _WIN32
	{
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(hStdin, &mode);
		SetConsoleMode(hStdin, mode & ~(ENABLE_QUICK_EDIT_MODE | ENABLE_INSERT_MODE));
	}
#endif
	// Włączenie obsługi myszy
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	// definiujemy kolory tekstu które użyjemy do kolorowania planszy
	ncurses_init_colors();
	// getch ma interpretować znaki specjalne takie jak KEY_UP
	keypad(stdscr, TRUE);
	// ustawiamy timeout dla getch (milisekundy)
	// po tym czasie program przejdzie dalej nawet jeśli nie podasz klawisza
	timeout(20);
	// podczas wpisywania z klawiatury nie powinna się drukować literka
	noecho();
	//nodelay(stdscr, TRUE);
	// ukrycie kursora
	curs_set(0);
}


int main(void) {
	// inicjalizacja ncurses
	WINDOW * mainwin = initscr();
	ncurses_config();
	Position position(50,24);
	Position enPosition(0, 0 );
	GameLogic* game = new GameLogic(20,5,0);
	std::vector<Entity*> entity;
	entity.emplace_back( new Player(position));
	entity.emplace_back(new Enemies(enPosition));
	entity.emplace_back(new Missile({0,0}));
	int input = 0;
	bool playing = true;

	while(playing) {
		input = getch();
		clear();
		for(int i = 0; i< entity.size(); i++)
			entity.at(i)->tick(input, game);
		game->tick();
		if(game->isplaying() == false) {
			clear();
			std::string word = "YOUR SCORE: " + std::to_string(game->getScore()) +  "\n play again y/n";
			move(game->getHeight()/2, 1);
			addstr(word.c_str());
			
			while(true) {

				input = getch();
				if(input == 'y') {
					for(int i = 0; i<entity.size(); i++)
					delete entity.at(i);
					delete game;
					entity.at(0) = new Player(position);
					entity.at(1) = new Enemies(enPosition);
					entity.at(2)= new Missile({0,0});
					game = new GameLogic(20, 5, 0);
					break;
				} else if(input == 'n') {
					playing = false;
					break;
				}
			}
		}




		refresh();

	}

// zakańczamy prace ncurses
	delwin(mainwin);
	endwin();
	refresh();
	return EXIT_SUCCESS;
}