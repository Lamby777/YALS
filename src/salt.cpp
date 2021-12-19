/*
 * salt.cpp
 *
 * - SALT -
 * Shell-Accessible Luxury Typewriter (lol)
 * Basic built-in Text Editor for YALS.
 *
 */

#include <iostream>
#include <ncurses.h>
#include <menu.h>
#include <signal.h>

using namespace std;

namespace salt {
int keyin(void) {
	int ch = getch();

	//if (ch != ERR) ungetch(ch);
	return ch;
}

string run() {
	// Init SALT
	cout.flush();
	bool running = true;
	string file = "";
	int curCol = 0;		// X
	int curLine = 0;	// Y

	// Override CTRL + C and CTRL + D
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);

	// Announce into terminal
	cout << "SALT running!" << endl;

	// Init ncurses
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	scrollok(stdscr, true);

	while (running) {
		int key = keyin();

		// If no key pressed
		if (key == -1)
			continue;

		// On ESC exit
		if (key == 27) {
			//printw("Received exit (ESC)\n");
			//refresh();
			running = false;
		} else {
			mvprintw(curCol, curLine, "%c\n", (char) key);
		}
	}

	endwin();
	return "SALT ended successfully";
}
}
