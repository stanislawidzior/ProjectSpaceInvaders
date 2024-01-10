#include <iostream>
#include <ncursesw/curses.h>
#include <fstream>
#ifdef _WIN32 // Sprawdzenie, czy kod jest kompilowany na Windows
#include <windows.h>
#endif
#include <unistd.h>
#include <vector>
class Position {
	private:
		int X=0;
		int Y=0;
	public:
		Position(int x, int y): X(x), Y(y) {}
		void incX(int j) {
			X+=j;
		}
		void incY(int j) {
			Y-=j;
		}
		int getY() const {
			return Y;
		}
		int getX() const {
			return X;
		}

};
class Missile {
	private:
		Position position;
	public:
		Missile(Position posi): position(posi) {
		}
		void setPosition (Position posit) {
			position = posit;
		}
		Position& getPosition() {
			return position;
		}
		void print() {
			move(position.getY(), position.getX());
			addch('*');
		}

};
class Entity {
		Position position;
		Position barrelPos;
		std::string fileName;
	protected:
		Position farRightPosition;
	public:
		Entity(Position posi, const std::string& fileName):position(posi), barrelPos(0,0), fileName(fileName), farRightPosition(posi) {
		}
		Position& getPosition() {
			return position;
		}
		Position& getFarRightPosition() {
			return farRightPosition;
		}
		Position getBarrelPosition() const {
			return barrelPos;
		}

		virtual void print() {
			std::ifstream sprite(fileName);
			if (!sprite.is_open()) {
				std::cerr << "Error missing file \"" << fileName << "\"" << std::endl;
				return;
			}

			std::string line;
			int yOffset = 0;
			while (std::getline(sprite, line)) {
				for (int i = 0; i < line.size(); i++) {
					move(position.getY() + yOffset, position.getX() + i);
					if (i == line.size() / 2 && yOffset == 0) {
						barrelPos.incX(position.getX() + i);
						barrelPos.incY(position.getY() + yOffset + 2);
					}
					addch(line.at(i));
				}
				yOffset++;
			}
			sprite.close();
		}
};

class Player : public Entity {
	public:
		Player(Position posi) : Entity(posi, "assets/player.txt") {
		}
};
class Enemies : public Entity {
	public:
		Enemies(Position posi) : Entity(posi, "assets/enemies.txt") {
			getFarRightPosition() = Position(posi.getX() + 6, posi.getY() + 2);
		}
};
bool checkHitbox(Position missile, Position entity, Position farRightPosition) {
	if( missile.getY() >= entity.getY() && missile.getY() <= farRightPosition.getY() && missile.getX() >= entity.getX() && missile.getX() <= farRightPosition.getX())
		return 1;																																									//DO GAME LOGIC
	else return 0;

}
void checkCollision(Player& player, std::vector<Missile>& missiles, std::vector<Enemies>& enemy) {
	int index;
	bool hit = false;
	for(int j = 0; j<enemy.size(); j++) {
		for(int i = 0; i < missiles.size(); i++) {

			if(checkHitbox(missiles.at(i).getPosition(), enemy.at(j).getPosition(), enemy.at(j).getFarRightPosition()) ) {									//DO GAME LOGIC
				missiles.erase(missiles.begin() + i);
				index = j;
				hit = true;
				break;
			}
			
		}
		if(hit) break;
	}
	if(hit)enemy.erase(enemy.begin()+index);
	
}


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
void generateEnemies(std::vector<Enemies>& enemy) {
	Position posi(50,10);																//DO GAMELOGIC
	for(int i = 1; i <=4 ; i++) {
		enemy.emplace_back(posi);
		posi.incX(7);
	}
}

int main(void) {
	// inicjalizacja ncurses
	WINDOW * mainwin = initscr();
	ncurses_config();
	Position position(50,24);
	Player player(position);
	//Player* player = new Player(position);
	//delete player
	Position enPosition(50, 10);
	std::vector <Enemies> enemy;
	generateEnemies(enemy);
	int direction = -1;
	int input = 0;
	int previous_input = 0;
	std::vector <Missile> missiles;
	//missiles.emplace_back(player.getPosition());
	int width=0, height=0;
	bool playing = true;
	bool shooting = false;
	unsigned int milisecond = 10000;
	int enmsMvDelay = 15;
		
		while(playing){
			getmaxyx(stdscr, height, width);
		input = getch();
		forerror(std::to_string(input));
		if(input != ERR)
			switch(input) {
				case 32:
					//missiles.at(0).setPosition(player.getPosition());
					missiles.emplace_back(player.getPosition());
					shooting=true;
					break;
				case KEY_LEFT:
					if(player.getPosition().getX() > 0)
						player.getPosition().incX(-1);
					break;
				case KEY_RIGHT:
					if(player.getPosition().getX()< width-14)
						player.getPosition().incX(1);
					break;
				case 'q':
				case 'Q':
					// wychodzimy z programu
					playing = false;
					break;
				default:
					// zmieniamy wyświetlany kursor
					break;
			};
		clear();				//ZAMIAST TEGO WSZYSTKIEGO DAC TICK I ZROBIC W PETLI WSZYSTKIE ELEMENTY GRY
		
		checkCollision(player, missiles, enemy);

		if(shooting) {

			for(int i = 0; i < missiles.size(); i++) {      //STRTZELANIE
				if(missiles.at(i).getPosition().getY() <= 0) {
					missiles.erase(missiles.begin()+i);
				} else {

					missiles.at(i).getPosition().incY(1);
					missiles.at(i).print();
				}
			}
		}
		player.print();
		enmsMvDelay--;
		if(enemy.at(0).getPosition().getX()  < 8 || enemy.at(enemy.size() - 1).getPosition().getX()>= width-14 ) {      	// ZAMIANA KIERUNKU PORUSZANIA OPONENTOW
			direction = direction *(-1);
		}

		if(enmsMvDelay == 0) {
			for(int i = 0; i < enemy.size(); i++)
				enemy.at(i).getPosition().incX(direction);										// PRZECIWNICY RUSZAJA SIE CO 15 ITERACJE PĘTLI
			enmsMvDelay = 15;
		}
		for(int i = 0; i < enemy.size(); i++) {
			enemy.at(i).print();
		}

		forerror(std::to_string(missiles.size()));
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
