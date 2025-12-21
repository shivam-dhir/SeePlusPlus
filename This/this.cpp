// this keyword can be used by member functions which belong to a class or struct.
// this is a pointer that points to the object for which the member function is called.
// this only works in non-static member functions because static member functions do not belong to any object.

#include <iostream>

// 'Forward declaring' the Example class so I can pass in a parameter of type Example* to the forward declaration of free function
// printExample below
class Example;
void printExample(Example*);

// when forward declaring, it is not necessary to mention the parameter name, only the type(s) is/are fine
void printExampleWithConst(const Example&);

class Example {

public:

	int value;

	// this is a pointer, so we use '->' to access members
	Example(int value) {
		this -> value = value;
	}

	// 'this' is a pointer to Example object, i.e. this is of type Example* 
	void print() {
		printExample(this);
	}

	void modifyValue(int newValue) const {
		//this->value = newValue; // this will cause a compilation error because the method is const
		// Error: cannot assign to non-static data member 'value' with const-qualified 'this'
	}

	// printExampleWithConst takes a const reference, so we need to dereference 'this' pointer
	// 'this' if type 'Example*' can be casted to 'const Example&'
	// 'this' is of type 'Example*' , so '*this' is of type Example&
	void redirectToPrint() {
		printExampleWithConst(*this);
	}

	void memberFunction() const {
		//this->value = 13; // not allowed since the method is const, we cannot modify member variables
		// Example* reference = this; // this is of type Example*, but will give error here because the function is const, which doesn't 
		// allow modifications of member variables
		// in this const function, refernce(of type Example*) can change the value of its member functions, which is not allowed 
		
		const Example* reference = this; // this is allowed, because we have defined reference as 'const', which restricts the reference 
		// from changing the membver variables
	}

};

void printExampleWithConst(const Example& e) {
	std::cout << e.value << std::endl;
}

void printExample(Example* e){
	std::cout << "print example class" << std::endl;
	std::cout << e-> value << std::endl;
}

int main() {
	std::cout << "Hello World" << std::endl;
}