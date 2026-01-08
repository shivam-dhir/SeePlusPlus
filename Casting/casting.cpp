// There are 2 types of casting:
// 1. C Style: manage casting yourself
// 2. C++ style: we have 4 types of casting operators available
// C style casting can do all of what C++ can, C++ just has syntactic sugar

// 4 Types of C++ casting:
// 1. Static Cast: High safety, performs conversions that are logically related
//				   Can be used when converting primitives. Casting is checked by compiler at compile time
//				   Is highly safe


//Use static_cast for most logic.
//Use dynamic_cast for class hierarchies.
//Use const_cast only when forced by external APIs.
//Use reinterpret_cast only for low - level system work.


#include <iostream>

class Animal { public: virtual void speak() {} }; // Must have a virtual function
class Dog : public Animal { public: void bark() {} };

void legacyFunction(char* str) { /* ... */ }

int main() {

	
	// 1.  static casting, happens at compile time
	// basic numeric conversion	
	float pi = 3.1476543f;
	int roundPi = static_cast<int>(pi);

	// static casting
	// converting void* back to typed pointer
	void* voidPtr = &roundPi; // void pointer can't be dereferenced. Since compiler doesn't know the type, it does not know how many bytes to read 
	int* intPtr = static_cast<int*>(voidPtr);

	// 2. Dynamic Casting
	// Happens at runtime. Used for downcasting (to convert base class pointer to derived class pointer)
	Animal* myPet = new Dog();

	// Try to treat the Animal as a Dog
	Dog* myDog = dynamic_cast<Dog*>(myPet);

	// checking if dynamic casting worked
	if (myDog) {
		myDog->bark(); // Success!
	}
	else {
		// Failure: myPet was not actually a Dog
	}

	// 3. Const Cast
	// used to manipulate the const or volatile nature of an object. It is the only C++ cast that can strip away "constness."
	// When to use: Usually when dealing with legacy APIs that take a char* but you know for a fact they won't modify the string.
	const char* message = "Hello";

	// Strip away const to satisfy the legacy function signature
	// using const_cast converts message from const char* to a char*
	legacyFunction(const_cast<char*>(message));

	// 4. Reinterpret Cast
	// Most powerful and dangerous cast
	// It tells the compiler to take the exact bits of one type and pretend they are another type, without any logic or conversion.
	// When to use: Low-level bit manipulation, hardware programming, or storing a pointer as an integer.
	// It offers very low safety

	long address = 0x7FFF1234;
	// Treat this memory address as a pointer to an integer
	int* pLocation = reinterpret_cast<int*>(address);
}