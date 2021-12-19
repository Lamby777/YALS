//============================================================================
// Name			: YALS.cpp
// Author		: Dex
// Version		: 0.1
// Copyright	: Licensed under GNU GPL 3.0
// Description	: Yet Another Linux Shell
//============================================================================

#include <iostream>
#include <signal.h>
#include "salt.h"

using namespace std;

// Current version-string of YALS, printed at start.
// Follows my own versioning syntax, because screw SemVer. >:)
string yalsVer = "d01";

// Prompt before terminal commands. Keep it simple!
string terminalPrompt = "{user} >> ";

struct yalsApp {
	auto run() {}
};

void yalsLog(string text) {
	cout << text << endl;
}

string replace(string text, string oldVal, string newVal) {
	return text.replace(text.find(oldVal), string(oldVal).size(), newVal);
}

void insertTerminalPrompt(void) {
	cout << replace(terminalPrompt, "{user}", getenv("USER"));
}

int main() {
	cout.flush();
	signal(SIGINT, SIG_IGN);

	yalsLog("Running YALS " + yalsVer);

	// REPL
	string cmd;
	insertTerminalPrompt();
	while (getline(cin, cmd)) {
		string output;

		if (cmd == "salt") output = salt::run();

		// Display output if exists
		if (output.length() > 0) yalsLog(output);

		// Prep next input
		insertTerminalPrompt();
	}

	// Cleanup

	// Return exit code 0
	return 0;
}
