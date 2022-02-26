//utility.cpp
#include "utility.h"
#include <iostream>
using namespace std;

int numAssign (string line) {
  int value = 0;
  //convert suites to num values (ascii values)
  //c->99, d->100, s->115, h->104+12->200 (lowercase)
  if (line[0] == 'h') {
    value += 200; //hearts 
  } else {
    value += line[0]; //all other suites are in order, can just use ascii
  }
  value *= 100; //multiply by 100 so cardPrinter can divide 
  //now convert ranks to num values
  //2-10->2-10, a->1, j->11, q->12, k->13
  //need to account 10 has two digits
  //1->49...9->57 ascii 
  if (line[2] <= 57 && line[2] > 49) { //2 - 9
    value += line[2]-48;
  } else if (line[2] == 'a') { //ace 
    value++;
  } else if (line[2] == 'j') { //jack
    value += 11;
  } else if (line[2] == 'q') { //queen
    value += 12;
  } else if (line[2] == 'k') { //king
    value += 13;
  } else { //10
    value += 10;
  } //value should be 3 digits for suite + 2 for rank
  return value;
}

bool compare (card* handA, card* handB) {
  int temp = handA->getMin();
  while(temp!=0) {
    if (handB->contains(temp)){
      return true; //returns true as long as at least 1 one match
    }
    temp = handA->getSuccessor(temp);
  }
  return false;
}

string cardPrinter (int value) {
  //first find the card's rank by dividing by 10 and 
  //taking the remainder 
  //use ASCII values for 2-9 (2->49)
  //update value case by case
  string rank;
  if (value%100 == 1) { //ace
    rank = 'a';
    value--;
  } else if (value%100 == 10) { //10
    rank = "10";
    value -= 10;
  } else if (value%100 == 11) { //jack
    rank = 'j';
    value -= 11;
  } else if (value%100 == 12) { //queen
    rank = 'q';
    value -= 12;
  } else if (value%100 == 13) { //king
    rank = 'k';
    value -= 13;
  } else {
    rank = 48 + value%100; //2-9
    value -= value%100;
  }
  value /= 100; //removes rank component of value 
  //200 for hearts, otherwise use ascii value
  string suite;
  if (value == 200) {
    suite = 'h'; //hearts
  } else {
    suite = value;
  }
  return suite + " " + rank;
}