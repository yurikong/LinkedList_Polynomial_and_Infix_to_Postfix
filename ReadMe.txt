This program converts polynomial string expression into linked list expression.
It also supports some functions of math operations (addition and multiplication).
The program converts a string expression to linked list expression by using stack and vector.
The idea is to split the polynomial expression by '+' and '-' and allocate the correct sign of the terms.
To extract coefficients and power of x variable and y variable, split the polynomial again by '*' and '^'.
Then store the numbers into linked list by conditions.

The program is implemented by a doubly linked list.
The program includes:
Node.h
LinkedList.h
Source.cpp
The program supports:
-a function that returns the highest power of an expression --- degree()
-a function that returns the coefficient of a term --- coefficient()
-a function that determines if two expressions are the same --- match()
-a function that adds two expression --- sum()
-a function that converts infix expression into postfix expression --- infixToPostFix()
-a function that multiply two expressions --- dot()

Notes:
In the beginning, we assume that an expression is ordered from high to low degree of variable x.
Program does not simpify or sort the result into high to low degree order after performing sum and dot.