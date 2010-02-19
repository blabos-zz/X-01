/*
 * string.h
 *
 *  Created on: 31/05/2009
 *      Author: wesley
 */

#ifndef STRING_H_
#define STRING_H_

#include <iostream>
using namespace std;


const int STR_MAX_LEN = 80;
typedef char string_t[STR_MAX_LEN];

int strlen(const char* str);
void strcpy(char* dest, const char* src);
void strcat(char* dest, const char* src);
void substr(char* sub, const char* orig, int from, int count);
void erase(char* str, int pos, int count);
int find(const char* str, char ch);
int rfind(const char* str, char ch);
int findstr(const char* phrase, const char* word);
void strpad(char* str, char ch = ' ', int count = STR_MAX_LEN);

//void init_string(string_t);

#endif /* STRING_H_ */
