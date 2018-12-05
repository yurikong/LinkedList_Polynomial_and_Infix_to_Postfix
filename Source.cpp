#include <iostream>
#include <vector>
#include <sstream>
#include "LinkedList.h"
using namespace std;

int main()
{
	// 1. express f using Node class and LinkedList class
	LinkedList f("5x^4*y^2+2x^2*y^3-6x^3*y^1-7x+6");
	cout << "1. f = "; f.print();
	// 2. degree() that will return the highest power of a term with a nonzero coefficient
	cout << "2. degree(): " << f.degree() << endl;
	// 3. coefficient(i) that will return the coefficient of i-th term
	cout << "3. coefficient(0): " << f.coefficient(0) << endl;
	// 4. match that will return true if the two expressions are the same, otherwise false
	LinkedList a("x^4*y^2-6x^3*y^1+2x^2-7x+6");
	LinkedList b("x^4*y^2-6x^3*y^1+2x^2-7x+6");
	LinkedList c("x^4*y^2-6x^3*y^1+2x^2-7x");
	cout << "4. match: ";
	a.match(b) ? cout << "true\t" : cout << "false\t";
	a.match(c) ? cout << "true\n" : cout << "false\n";
	// 5. sum that will add the expressions
	LinkedList y("5x^4*y^2-6x^3+2x^2*y^1-7x+6");
	LinkedList z("3x^2*y^1+4x*y^2+7");
	y = y.sum(z);
	cout << "5. sum: ";
	y.print();
	// 6. converts an infix expression to postfix expression
	cout << "6. infix to postfix: " << f.infixToPostfix() << endl;
	// 7. dot that will multiple the expressions
	y = y.dot(z);
	cout << "7. dot: ";
	y.print();
	cout << endl;
	system("pause");
	return 0;
}