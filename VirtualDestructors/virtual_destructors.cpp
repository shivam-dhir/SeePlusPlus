#include <iostream>

class Base {

public:
	Base() {
		std::cout << "Base constructor" << std::endl;
	}
	
	// Base destructor is declared as virtual to ensure that when a Base pointer points to a Derived object, the Derived destructor is called when the Base pointer is deleted. This allows for proper cleanup of resources allocated in the Derived class.
	virtual ~Base() {
		std::cout << "Base destructor called" << std::endl;
	}
};

// Derived class consists of a Base sub-object, and the Base sub-object is constructed before the Derived class constructor
// So, when a Derived object is created, the Base constructor is called first, and then the Derived constructor is called.
// Destructor is called in the reverse order of constructor, so when a Derived object is destroyed, the Derived destructor is called first, and then the Base destructor is called.
class Derived : public Base {

private:
	int* data; // Example of a resource that might be allocated in the Derived class

public:
	Derived() {
		data = new int[10]; // Allocating resources in the Derived class constructor
		std::cout << "Derived constructor" << std::endl;
	}
	
	~Derived() {
		std::cout << "Derived destructor" << std::endl;
	}

};

int main() {
	// Base constructor is called
	Base* ptr = new Base();

	// Base destructor is called
	delete ptr;

	std::cout << "---------------------------------------------" << std::endl;

	// Base constructor is called, then Derived constructor is called
	Derived* dptr = new Derived();
	
	// Derived destructor is called, then Base destructor is called
	delete dptr;

	std::cout << "---------------------------------------------" << std::endl;

	// Inheritance and polymorphism: when a Base pointer points to a Derived object, the Base constructor is called first, then the Derived constructor is called.
	Base* bptr = new Derived();
	
	// When a Base pointer points to a Derived object, the Base destructor is called
	// In this case, only the Base destructor is called, and the Derived destructor is not called because the Base destructor is not virtual and hence not custom created/overriden. This can lead to resource leaks if the Derived class allocates resources that need to be released in its destructor.
	// This is harmful because the Derived destructor is not called, and any resources allocated in the Derived class will not be released, leading to memory leaks or other resource leaks.
	delete bptr;
}