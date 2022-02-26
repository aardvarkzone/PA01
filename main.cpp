#include "cards.h"
#include "utility.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main (int argv, char** argc){
  if (argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]); //handA
  ifstream cardFile2 (argc[2]); //handB
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  int value = 0;
  card handA;
  //Read each file and insert in hands
  while (getline (cardFile1, line) && (line.length() > 0)){
    value = numAssign(line);
    handA.insert(value);
    value = 0;
  }
  cardFile1.close();

  card handB;
  while (getline (cardFile2, line) && (line.length() > 0)){
    value = numAssign(line);
    handB.insert(value);
    value = 0;
  }
  cardFile2.close();
  
  while (compare(&handA, &handB)){
    value = handA.getMin();
    //because Alice goes from min->max, start with min 
    //and then set the next value to be the successor 
    //then remove the same val between A and B
    while (!(handB.contains(value) && handA.contains(value))){
      value = handA.getSuccessor(value);
    }
    handA.remove(value);
    handB.remove(value);
    cout << "Alice picked matching card " << cardPrinter(value) << endl;
    
    if (compare(&handA, &handB)) {
      //same logic as above but now start with max
      //and go down with getPredecessor 
      value = handB.getMax();
      while (!(handA.contains(value)&&handB.contains(value))){
        value = handB.getPredecessor(value);
      }
      handA.remove(value);
      handB.remove(value);
      cout << "Bob picked matching card " << cardPrinter(value) << endl;
    }
  }

  //now prints remaining cards in both hands starting at min
  //getSuccessor for next card, cardPrinter to print from val
  cout << "\nAlice's cards: " << endl;
  int aliceCard = handA.getMin();
  
  while (aliceCard != 0 && aliceCard < 100000) {
    cout << cardPrinter(aliceCard) << " " << aliceCard << endl;
    aliceCard = handA.getSuccessor(aliceCard);
  }

  cout << "\nBob's cards: " << endl;
  int bobCard = handB.getMin();
  while (bobCard != 0 && bobCard < 100000) {
    cout << cardPrinter(bobCard) << endl;
    bobCard = handB.getSuccessor(bobCard);
  }

  return 0;
}
