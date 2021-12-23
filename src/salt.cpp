/*
 * salt.cpp
 *
 * - SALT -
 * Shell-Accessible Luxury Typewriter (lol)
 * Basic built-in Text Editor for YALS.
 *
 */

#include <iostream>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <ncurses.h>
#include <menu.h>
#include <signal.h>

using namespace std;

namespace salt {

string file = "";
vector<string> content = { "" };
int curX = 0;	// X
int curY = 0;	// Y

char* substr(const char *input, int offset, int len, char *dest) {
	int input_len = strlen(input);

	if (offset + len > input_len) {
		return NULL;
	}

	strncpy(dest, input + offset, len);
	return dest;
}

int keyin(void) {
	int ch = getch();

	//if (ch != ERR) ungetch(ch);
	return ch;
}

void insertNewLine(int x, int y, bool causedByUser) {
	// Split line into half at X
	const char* cy = content[y].c_str();

	char* beforeCut = NULL;
	substr(cy, 0, x, beforeCut);
	char* afterCut = NULL;
	substr(cy, x, (strlen(cy) - x)-1, afterCut);

	// Add new line after Y
	content.insert(content.begin() + y, afterCut);

	// Set old line to cut version
	content[y] = beforeCut;

	if (causedByUser) {
		curX = 0;
		curY = y + 1;
	}
}

void putCharToFile(int x, int y, char ch) {
	// Insert into vector
	content[y][x] = ch;
	mvprintw(5, 0, "%i", x);
	mvprintw(5, 5, "%i", y);
	for (int i = 0; i < (int) content.size(); i++)
		mvprintw(6 + i, 0, content[i].c_str());
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
		} else if (key == KEY_LEFT) { // Left
			curX--;
		} else if (key == KEY_RIGHT) { // Right
			curX++;
		} else if (key == KEY_UP) { // Up
			curY--;
		} else if (key == KEY_DOWN) { // Down
			curY++;
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
