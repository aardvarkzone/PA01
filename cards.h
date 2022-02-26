//cards.h
//All class declarations go here
#ifndef CARDS_H
#define CARDS_H
#include <iostream>
using namespace std;

class card {
 public:
    card();                   // constructor
    ~card();                  // destructor
    bool insert(int value);     // insert value; return false if duplicate
    void printPreOrder() const; // prints tree data pre-order to cout

    void printInOrder() const;       // print tree data in-order to cout
    void printPostOrder() const;     // print tree data post-order to cout
    int sum() const;                 // sum of all values
    int count() const;               // count of values
    bool contains(int value) const;  // true if value is in tree

    int getPredecessor(int value) const;       // returns the predecessor value of the given value or 0 if there is none
    int getSuccessor(int value) const;         // returns the successor value of the given value or 0 if there is none
    bool remove(int value);                    // deletes the Node containing the given value from the tree

    int getMin() const; // returns min
    int getMax() const; // returns max

 private:
    struct Node {
	    int info;
	    Node *left, *right, * parent;
        Node(int v=0) : info(v), left(0), right(0), parent(0) { }
    };
    Node* root;
    Node* getNodeFor(int value, Node* n) const; // returns the node for a given value or NULL if none exists
    void clear(Node *n); // for destructor
    bool insert(int value, Node *n); // note overloading names for simplicity
    void printPreOrder(Node *n) const;
    void printInOrder(Node *n) const;
    void printPostOrder(Node *n) const;
    int sum(Node *n) const;
    int count(Node *n) const;

    Node* getSuccessorNode(int value) const;   // returns the Node containing the successor of the given value
    Node* getPredecessorNode(int value) const; // returns the Node containing the predecessor of the given value 
};


#endif