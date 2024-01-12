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
	timeout(10);
	// podczas wpisywania z klawiatury nie powinna się drukować literka
	noecho();
	//nodelay(stdscr, TRUE);
	// ukrycie kursora
	curs_set(0);
}
void forerror(std::string word) {
	int i = 0;
	//word = "";
	while(i < word.size()) {
		move(15, 15+i);
		addch(word.at(i));
		i++;
	}

}

void print_board(int x, int y, int character) {
	// operujemy na wirtualnym ekranie będącym buforem ekranu
	// a następnie wyświetlamy bufor w terminalu funkcją refresh

	clear(); // czyści wirtualny ekran (lepiej było by czyścić jeden znak albo jedna linie)

	attron(COLOR_PAIR(1)); // ustawiamy wcześniej zdefiniowaną perę kolorów
	// (można użyć mvaddch zamiast dwóch funcji)
	move(y, x); // skaczemy kursorem do danej pozycji
	addch(character); // drukujemy podany znak
	//move(0, 0); // aby migający kursor nam nie przeszkadzał
	attroff(COLOR_PAIR(1)); // przywracamy domyślny kolor

	refresh(); // wyświetlamy zawartość wirtualnego ekranu dopiero po refresh
}


int main(void) {
	// inicjalizacja ncurses
	WINDOW * mainwin = initscr();
	ncurses_config();
	Position position(50,24);
	Position enPosition(50, 10);
	GameLogic* game = new GameLogic(10,15,0,3);
	Entity* proba = new Player(position);
	Entity* proba2 = new Enemies(enPosition);
	//Entity* proba3 = new Missile({0,0});
	int direction = -1;
	int input = 0;
	int width=0, height=0;
	bool playing = true;

	while(playing) {
		input = getch();
		clear();	
			move(15,15);
	//addstr("gownogowno");
			proba->tick(input, game);
			proba2->tick(input, game);
			game->tick();
	

	//
				//ZAMIAST TEGO WSZYSTKIEGO DAC TICK I ZROBIC W PETLI WSZYSTKIE ELEMENTY GRY




	//forerror(std::to_string(missiles.size()));
	//missiles.at(0).print();
	//previous_input = input;

	//input = 0;
	refresh();

}

// zakańczamy prace ncurses
delwin(mainwin);
endwin();
refresh();
return EXIT_SUCCESS;
}