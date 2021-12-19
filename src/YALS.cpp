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

using std::cout;
using std::cin;
using std::string;
using std::endl;

string yalsVer = "d01";
string terminalPrompt = ">> ";

struct yalsApp {
	auto run() {}
};

void yalsLog(string text) {
	cout << text << endl;
}

int main() {
	cout.flush();
	signal(SIGINT, SIG_IGN);

	yalsLog("Running YALS " + yalsVer);

	// REPL
	string cmd;
	cout << terminalPrompt;
	while (std::getline(cin, cmd)) {
		string output;

		if (cmd == "salt") output = salt::run();

		// Display output if exists
		if (output.length() > 0) yalsLog(output);

		// Prep next input
		cout << terminalPrompt;
	}

	// Cleanup

	// Return exit code 0
	return 0;
}
