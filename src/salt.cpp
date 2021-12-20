/*
 * salt.cpp
 *
 * - SALT -
 * Shell-Accessible Luxury Typewriter (lol)
 * Basic built-in Text Editor for YALS.
 *
 */

#include <iostream>
#include <vector>
#include <unistd.h>
#include <ncurses.h>
#include <menu.h>
#include <signal.h>

using namespace std;

namespace salt {

string file = "";
vector<string> content = {string("")};
int curX = 0;	// X
int curY = 0;	// Y

int keyin(void) {
	int ch = getch();

	//if (ch != ERR) ungetch(ch);
	return ch;
}

void insertNewLine(int x, int y, bool causedByUser) {
	// Split line into half at X
	string beforeCut = content[y].substr(0, x);
	string afterCut = content[y].substr(x+1);

	// Add new line after Y
	content.insert(content.begin() + (y+1), afterCut);

	// Set old line to cut version
	content[y] = beforeCut;

	/*if (causedByUser) {
		curX = 0;
		curY = y+1;
	}*/
}

void putCharToFile(int x, int y, char ch) {
	// Insert into vector
	content[y][x] = ch;
	mvprintw(5, 0, "%i", x);
	mvprintw(5, 5, "%i", y);
	for(int i = 0; i < (int) content.size(); i++)
	    mvprintw(6+i, 0, "%s", content[i]);
	// Insert into terminal
	mvprintw(y, x, "%c", ch);
}

string run() {
	// Init SALT
	cout.flush();
	bool running = true;

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
		} else if (key == 10) {
			insertNewLine(curX, curY, true);
		} else {
			putCharToFile(curX, curY, (char) key);
			curX++;
		}
	}

	endwin();
	return "SALT ended successfully";
}
}
