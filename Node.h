#pragma once
#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class Node
{
public:
	// constructors
	Node(int c = 0, int x = 0, int y = 0) : coeff(c), xPower(x), yPower(y), prev(NULL), next(NULL) {}
	// setters
	void setC(int c) { coeff = c; }       // update coefficient
	void setX(int x) { xPower = x; }      // update degree of x
	void setY(int y) { yPower = y; }      // update degree of y
	void setPrev(Node* p) { prev = p; }  // link to previous node
	void setNext(Node* p) { next = p; }  // link to next node
	// getters
	int getC() const { return coeff; }       // return coefficient
	int getX() const { return xPower; }       // return degree of x
	int getY() const { return yPower; }      // return degree of y
	Node* getPrev() const { return prev; } // return previous node
	Node* getNext() const { return next; }  // return next node
private:
	int coeff;              // coefficient
	int xPower;             // degree of x
	int yPower;             // degree of y
	Node* prev;             // left link
	Node* next;             // right link
};

#endif