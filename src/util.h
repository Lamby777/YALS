/*
 * util.h
 *
 *  Created on: Dec 23, 2021
 *      Author: dex
 */

#ifndef UTIL_H_
#define UTIL_H_

using std::string;

namespace util {

string replace(string text, string oldVal, string newVal);
char* substr(const char* input, int offset, int len, char *dest);

}

#endif /* UTIL_H_ */
