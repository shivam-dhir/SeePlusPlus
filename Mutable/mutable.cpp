#include <iostream>

// Mutable is usually used to allow modification of class member variables
// even when they are part of an object that is declared as const.
// It is used when a function is logically const, but needs to modify some internal state.

class Entity {
private:
	int var1 = 9;
	mutable int counter = 0;

public:
	// marking this function as const means it cannot modify any member variables
	const int& getVariable() const {
		counter++; // this is valid as counter is marked as mutable even though the function is const
		return var1;	
	}
};

int main() {

	int x = 10;
	// by default, lambda captures are const, so we need to use mutable keyword if we want to modify captured variables
	// inside the sqaure brackets, we need to specify how to capture variables, = means capture by value, & means capture by reference, this means capture the this pointer
	
	// lambda function
	// we are capturing by value here, which does not allow modification of x inside the lambda
	auto f = [=]() {
			x++; // invalid, error: increment of read-only variable 'x'
			std::cout << x << std::endl;
		};

	auto fn1 = [=]() mutable {
		x++; // valid, because the lambda is marked as mutable which allows modification of captured variables
		// using mutable creates a copy of the captured variables that can be modified inside the lambda,
		// and does not affect the original variable outside the lambda
		std::cout << x << std::endl;
		};
	//x = 10; original x remains unchanged

	auto fn = [&]() {
		x++; // valid, because we are capturing by reference
		std::cout << x << std::endl;
		};

	// calling lambda function
	fn();
}