//cards.cpp
//Author: Advait Arumugam
//Implementation of the classes defined in cards.h

#include "cards.h"

// constructor sets up empty tree
card::card() : root(0) { }

// destructor deletes all nodes
card::~card() {
    // cout << "Root is being destroyed: " << root->info;
    clear(root);
}

// recursive helper for destructor
void card::clear(Node*n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool card::insert(int value) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool card::insert(int value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
	if (n->left)
	    return insert(value, n->left);
	else {
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(value, n->right);
	else {
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
    }
}

// print tree data pre-order
void card::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void card::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void card::printInOrder() const {
    printInOrder(root);
}

void card::printInOrder(Node *n) const {
    if (n) {
        printInOrder(n->left);
        cout << n->info << " ";
        printInOrder(n->right);
    }
}

// prints tree data post-order, with helper
void card::printPostOrder() const {
    printPostOrder(root);
}

void card::printPostOrder(Node *n) const {
    if (n) {
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout << n->info << " ";
    }
}

// return sum of values in tree
int card::sum() const {
    return sum(root);
}

// recursive helper for sum
int card::sum(Node *n) const {
    if (n == nullptr) {
        return 0;
    }
    return (n->info + sum(n->left) + sum(n->right));
}

// return count of values
int card::count() const {
    return count(root);
}

// recursive helper for count
int card::count(Node *n) const {
    
    if (n == nullptr) {
        return 0;
    }
    return (1 + count(n->left) + count(n->right));
    // REPLACE THIS NON-SOLUTION
}

// returns the node for a given value or NULL if none exists
card::Node* card::getNodeFor(int value, Node* n) const{
    Node* p = n;
    while(p){
        if(value == p->info){
            return p;
        } else if(value < p->info){
            p = p->left;
        } else{
            p = p->right;
        }
    }
    return nullptr;
}

// returns true if value is in the tree; false if not
bool card::contains(int value) const {
    return getNodeFor(value, root);
}

// returns the Node containing the predecessor of the given value
card::Node* card::getPredecessorNode(int value) const{
    if(!contains(value)){
        return nullptr;
    }
    else{
        Node* p = getNodeFor(value, root);
        if(p->left){
            p = p->left;
            while (p)
            {
                if(p->right){
                    p = p->right;
                } else{
                    break;
                }
            }
        }
        else{
            while (p->parent) {
                if(p->parent->info >= value){
                    p = p->parent;
                } else{
                    break;
                }
            }
        
            return p->parent;
        }
        return p;
    }
}

// returns the predecessor value of the given value or 0 if there is none
int card::getPredecessor(int value) const{
    if(getPredecessorNode(value)){
        return getPredecessorNode(value)->info;
    } else{
        return 0;
    }
}

// returns the Node containing the successor of the given value
card::Node* card::getSuccessorNode(int value) const{
    if(!contains(value)){
        return nullptr;
    }
    else{
        Node* p = getNodeFor(value, root);
        if(p->right){
            p = p->right;
            while (p)
            {
                if(p->left){
                    p = p->left;
                } else{
                    break;
                }
            }
        }
        else{
            while (p->parent) {
                if(p->parent->info <= value){
                    p = p->parent;
                } else{
                    break;
                }
            }
        
            return p->parent;
        }
        return p;
    }
}

    // returns the successor value of the given value or 0 if there is none
int card::getSuccessor(int value) const{
    if(getSuccessorNode(value)){
        return getSuccessorNode(value)->info;
    } else{
        return 0;
    }
}

bool card::remove(int value){
    Node* p = getNodeFor(value, root);
    if(!contains(value)){return false;}
    if(p != nullptr && (p->right == nullptr && p->left == nullptr)){ 
        if(p->parent == nullptr){
            root = nullptr;
        } else if(p->parent->left == p){
            p->parent->left = nullptr;
        } else{
            p->parent->right = nullptr;
        } 
        delete p;
        return true;
    }
    else if(p != nullptr && p->right == nullptr){
        if(p->parent == nullptr){
            root = p->left;
        }else if(p->parent->left == p){
            p->left->parent = p->parent;
            p->parent->left = p->left;
        }else{
            p->left->parent = p->parent;
            p->parent->right = p->left;
        } 
        delete p;
        return true;
    }
    else if(p != nullptr && p->left == nullptr){
        if(p->parent == nullptr){
            root = p->right;
        }else if(p->parent->left == p){
            p->right->parent = p->parent;
            p->parent->left = p->right;
        }else{
            p->right->parent = p->parent;
            p->parent->right = p->right;
        } 
        delete p;
        return true;
    }else{
        Node* succ = getSuccessorNode(value);
        int tempVal = succ->info;
        remove(tempVal);
        p->info = tempVal;
        return true;
    }
}



int card::getMin() const{
    Node* n = root;
    while(n->left){
        n = n->left;
    }
    return n->info;
}
    
int card::getMax() const{ 
    Node* n = root;
    while(n->right){
        n = n->right;
    }
    return n->info;
}