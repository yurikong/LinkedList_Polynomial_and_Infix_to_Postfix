#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "Node.h"
#include <string>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;

class LinkedList
{
public:
	LinkedList() // default constructor
	{
		n = 0;  // set size
		header = new Node; // request memory
		trailer = new Node; // request memory
		header->setNext(trailer); // link header to trailer
		trailer->setPrev(header); // link trailer to header
		expr = ""; // set expr
	}
	LinkedList(string s) // constructor with one argument
	{
		header = new Node; // request memory
		trailer = new Node; // request memory
		header->setNext(trailer); // set header
		trailer->setPrev(header); // set trailer
		n = 0; // set size
		expr = s; // set expr
		load(s); // extract coefficient, power of x, and power of y into nodes
	}
	int size() const { return n; } // get size
	bool empty() const { return size() == 0; } // is empty
	int degree() const // return highest degree of expression
	{
		int max = 0;
		if (!empty())
		{
			Node* cur = header->getNext();
			max = cur->getX() + cur->getY();
			while (cur != trailer) // find highest degree
			{
				cur = cur->getNext();
				int num = cur->getX() + cur->getY();
				if (num > max)
					max = num;
			}
		}
		return max;
	}
	int coefficient(int index) const // return coefficient of i-th term
	{
		if (index >= 0 && index < size())
		{
			Node* cur = header->getNext();
			for (int i = 0; i < index; i++) // traverse the list
				cur = cur->getNext();
			return cur->getC();
		}
		return NULL;
	}
	bool match(const LinkedList& L) const { return expr == L.expr; } // are two expressions the same?
	LinkedList sum(const LinkedList& L) // sum of two expressions
	{
		LinkedList temp;
		Node* p = header->getNext();
		Node* v = L.begin()->getNext();
		while (p != trailer)
		{
			while (v != L.end())
			{
				if (p->getX() == v->getX() && p->getY() == v->getY())
				{
					int c = p->getC() + v->getC();
					int x = p->getX();
					int y = p->getY();
					Node* n = new Node;
					n->setC(c);
					n->setX(x);
					n->setY(y);
					temp.add(n);
				}
				v = v->getNext();
			}
			v = L.begin()->getNext();
			p = p->getNext();
		}
		Node* m = header->getNext();
		while (m != trailer)
		{
			if (!temp.hasSameExp(m))
			{
				int c = m->getC();
				int x = m->getX();
				int y = m->getY();
				Node* s = new Node;
				s->setC(c);
				s->setX(x);
				s->setY(y);
				temp.add(s);
			}
			m = m->getNext();
		}
		Node* n = L.begin()->getNext();
		while (n != L.end())
		{
			if (!temp.hasSameExp(n))
			{
				int c = n->getC();
				int x = n->getX();
				int y = n->getY();
				Node* t = new Node;
				t->setC(c);
				t->setX(x);
				t->setY(y);
				temp.add(t);
			}
			n = n->getNext();
		}
		return temp;
	}
	string infixToPostfix() const // infix to postfix
	{
		string postfix = "";
		stack<char> S;
		for (int i = 0; i < expr.length(); i++)
		{
			if (isOperand(expr[i]))
				postfix += expr[i];
			else if (isOperator(expr[i]))
			{
				while (!S.empty() && isHigherPrec(S.top(), expr[i]))
				{
					postfix += S.top();
					S.pop();
				}
				S.push(expr[i]);
			}
		}
		while (!S.empty())
		{
			postfix += S.top();
			S.pop();
		}
		return postfix;
	}
	LinkedList dot(const LinkedList& L) // multiply two expressions
	{
		LinkedList result;
		Node* p = header->getNext();
		Node* v = L.begin()->getNext();
		while (p != end())
		{
			int c = p->getC();
			int x = p->getX();
			int y = p->getY();
			while (v != L.end())
			{
				int _c = v->getC();
				int _x = v->getX();
				int _y = v->getY();
				int coeff = c * _c;
				int xPower = x + _x;
				int yPower = y + _y;
				Node* n = new Node;
				n->setC(coeff);
				n->setX(xPower);
				n->setY(yPower);
				result.add(n);
				v = v->getNext();
			}
			v = L.begin()->getNext();
			p = p->getNext();
		}
		return result;
	}
	void print() const // print list
	{
		Node* p = header->getNext();
		while (p != trailer)
		{
			cout << p->getC() << '/' << p->getX() << '/' << p->getY() << " -> ";
			p = p->getNext();
		}
		cout << "NULL";
		cout << endl;
	}
	Node* begin() const { return header; }
	Node* end() const { return trailer; }
private:
	bool isOperand(char ch) const // infix to postfix helper function
	{
		if ((ch >= '0' && ch <= '9') || ch == 'x' || ch == 'y')
			return true;
		return false;
	}
	bool isOperator(char ch) const // infix to postfix helper function
	{
		if (ch == '+' || ch == '-' || ch == '*' || ch == '^')
			return true;
		return false;
	}
	int opWeight(char ch) const // infix to postfix helper function
	{
		int weight = 0;
		switch (ch)
		{
		case('+'): { weight = 1; break; }
		case('-'): { weight = 1; break; }
		case('*'): { weight = 2; break; }
		case('^'): {weight = 3; break; }
		};
		return weight;
	}
	bool isHigherPrec(char l, char f) const // infix to postfix helper function
	{
		int weight1 = opWeight(l);
		int weight2 = opWeight(f);
		return weight1 >= weight2;
	}

	vector<char> signs(string s) const // get signs of terms
	{
		vector<char> sign;
		if (s[0] != '-')
			sign.push_back('+');
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == '-')
				sign.push_back('-');
			if (s[i] == '+')
				sign.push_back('+');
		}
		return sign;
	}
	vector<string> split(string s) const // convert expression into linked list expression helper function
	{
		istringstream ss(s);
		string token;
		vector<string> temp;
		while (getline(ss, token, '-'))
			temp.push_back(token);
		vector<string> v;
		for (int i = 0; i < temp.size(); i++)
		{
			istringstream iss(temp[i]);
			string tk;
			while (getline(iss, tk, '+'))
				v.push_back(tk);
		}
		return v;
	}
	vector<string> splitToTerms(string s) const // convert expression into linked list expression helper function
	{
		istringstream iss(s);
		string token;
		vector<string> temp;
		while (getline(iss, token, '*'))
			temp.push_back(token);
		vector<string> v;
		for (int i = 0; i < temp.size(); i++)
		{
			istringstream ss(temp[i]);
			string tk;
			while (getline(ss, tk, '^'))
				v.push_back(tk);
		}
		return v;
	}
	bool isXTerm(string s) const // convert expression into linked list expression helper function
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == 'x')
				return true;
		}
		return false;
	}
	bool isYTerm(string s) const // convert expression into linked list expression helper function
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == 'y')
				return true;
		}
		return false;
	}
	void load(string s) // convert expression into linked list expression
	{
		vector<string> terms = split(s);
		for (int i = 0; i < terms.size(); i++)
		{
			int c = 0, x = 0, y = 0;
			vector<string> temp = splitToTerms(terms[i]);
			for (int j = 0; j < temp.size(); j++)
			{
				if (isXTerm(temp[j]))
				{
					if (temp[j][0] == 'x')
						c = 1;
					else
					{
						string str = temp[j].substr(0, temp[j].length() - 1);
						c = stoi(str);
					}
					if (j + 1 < temp.size()&& temp[j+1] != "y")
						x = stoi(temp[j + 1]);
					else
						x = 1;
					j++;
				}
				else if (isYTerm(temp[j]))
				{
					if (j + 1 < temp.size())
						y = stoi(temp[j + 1]);
					else
						y = 1;
					j++;
				}
				else
				{
					c = stoi(temp[j]);
					x = 0;
					y = 0;
				}
			}
			Node* p = new Node;
			p->setC(c);
			p->setX(x);
			p->setY(y);
			add(p);
		}
		vector<char> sign = signs(s);
		Node* v = header->getNext();
		for (int i = 0; i < sign.size(); i++)
		{
			if (sign[i] == '-')
				v->setC(-1 * v->getC());
			v = v->getNext();
		}
	}
	bool hasSameExp(Node* p) const // sum helper function
	{
		Node* v = header->getNext();
		while (v != trailer)
		{
			if (v->getX() == p->getX() && v->getY() == p->getY())
				return true;
			v = v->getNext();
		}
		return false;
	}
	void add(Node* p) // add term
	{
		Node* v = trailer->getPrev();
		v->setNext(p);
		p->setNext(trailer);
		trailer->setPrev(p);
		p->setPrev(v);
		n++;
	}
private:
	int n; // size
	string expr; // expression
	Node* header; // dummy header
	Node* trailer; // dummy trailer
};

#endif