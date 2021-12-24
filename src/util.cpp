/*
 * Helper functions for the rest of this project
 */

#include <iostream>
#include <string.h>

using namespace std;

namespace util {

string replace(string text, string oldVal, string newVal) {
	return text.replace(text.find(oldVal), string(oldVal).size(), newVal);
}

char* substr(const char* input, int offset, int len, char *dest) {
	int input_len = strlen(input);

	if (offset + len > input_len) {
		return NULL;
	}

	strncpy(dest, input + offset, len);
	return dest;
}

}
