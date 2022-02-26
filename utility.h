//utility.h
#ifndef UTIL_H
#define UTIL_H
#include "cards.h"
#include <iostream>
using namespace std;

//combines card rank + suite into 1 numerical value
int numAssign (string line);
//checks for equal card values between two hands
bool compare (card* handA, card* handB);
//converts value from numAssign back to card rank + suite
string cardPrinter (int value);

#endif