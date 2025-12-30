#include <iostream>

int main() {

	// lamdas can be used where function pointers are used
	// lambdas are inline, anonymous functions which are discarded after use

	// lambda is a function, which can't be assigned to a type like int, float, char etc
	// int sum = [](int x, int y) { return x + y; }(3, 4); // invalid

	// we can assign a lambda to a function pointer
	int (*add)(int, int) = [](int x, int y) { return x + y; };
	int sum = add(3, 4);

	// OR
	
	// recommended (lambdas to auto)
	auto multiply = [](int x, int y) { return x * y; };
	int result = multiply(3, 4);

	// to capture variables from the surrounding scope, we can use capture clauses inside the square brackets []
	// [=] -> captures all variables by value, [&] -> captures all variables by reference, [x, &y] -> captures x by value and y by reference
	// [this] -> captures the this pointer by value, [] -> capture nothing

	int a = 10, b = 5;
	// capture a by value
	auto addTen = [a](int x) {return x + a; };
	// capture by value
	// mutable allows modification of captured variables
	auto subTen = [=](int x) mutable { a = 98;  return x - a; };
	// capture by reference
	auto multTen = [&](int x) {return x * a; };

}