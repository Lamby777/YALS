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

int yalsVer = 50;
string terminalPrompt = ">> ";

int main() {
	cout.flush();
	signal(SIGINT, SIG_IGN);

	cout << "Running YALS v" << yalsVer << endl;

	// REPL
	string cmd;
	cout << terminalPrompt;
	while (std::getline(cin, cmd)) {
		cout << terminalPrompt;

		string output;

		if (cmd == "salt") output = salt::run();

		// Display output if exists
		if (output.length() > 0) {
			cout << output << endl;
		}
	}

	// Cleanup

	// Return exit code 0
	return 0;
}
