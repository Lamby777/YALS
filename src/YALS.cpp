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
#include "colors.h"
#include "util.h"

using namespace std;

// Current version-string of YALS, printed at start.
// Follows my own versioning syntax, because screw SemVer. >:)
string yalsVer = "d01";

// Prompt before terminal commands. Keep it simple!
string terminalPrompt = "{user} >> ";

// Message for commands not found
string yalsCmd404Msg = "Command not found...";



struct yalsApp {
	auto run() {}
};

void yalsLog(string text) {
	cout << text << endl;
}

void insertTerminalPrompt(void) {
	cout << util::replace(terminalPrompt, "{user}", BOLDGREEN + string(getenv("USER")) + RESET);
}

string resolveCommand(string cmd) {
	if (cmd == "salt") return salt::run();
	return yalsCmd404Msg;
}

int main() {
	cout.flush();
	signal(SIGINT, SIG_IGN);

	yalsLog(string(BOLDAQUA) + "Running YALS " + BOLDRED + yalsVer + RESET);

	// REPL
	string cmd;
	insertTerminalPrompt();
	while (getline(cin, cmd)) {
		// Prevent empty commands
		if (cmd.length() != 0) {
			// Run command (or give "not found" error)
			string output = resolveCommand(cmd);

			// Display output if exists
			if (output.length() > 0) yalsLog(output);
		}

		// Prep next input
		insertTerminalPrompt();
	}

	// Cleanup

	// Return exit code 0
	return 0;
}
