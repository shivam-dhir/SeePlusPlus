// objects on the stack have a certain lifetime/scope
// when the particular function/class/method goes out of scope, its corresponding variables/states/conditions go out of scope

// objects on the heap remain alive as long as the program is running

#include <iostream>

class Example;

class ScopedPointer {
private:
	// pointer to Example instance which is stored on the heap
	Example* m_ptr;

public:
	ScopedPointer(Example* ptr): m_ptr(ptr) {}

	// when the ScopedPointer instance goes out of scope/is destroyed, the destructor will delete the pointer to Example (m_ptr), which is stored on the heap
	// this is the basic idea of smart pointers
	~ScopedPointer() {
		delete m_ptr;
	}
};

class Example {
public:

	// Example constructor
	Example() {
		std::cout << "Example Instance Created" << std::endl;
	}

	// Example destructor
	~Example() {
		std::cout << "Example Instance Destroyed" << std::endl;
	}
};

// below function is bad practice and should be avoided
// we are returning a pointer to an array which has been created on the stack and is about to be destroyed as the function ends
// so the pointer we return now points to nothing, which creates a dangling pointer problem
int* createArray() {
	int array[10]; // array points to the address of the first element in the array
	// array is of type 'int*'
	return array;
}

int main() {

	{
		// Default constructor called
		//Example e;
		// e is only defined in this scope. when this scope/block ('{}') ends, instance 'e' will be destroyed 
	}
	// when instance e is created in the above scope, it calls the default constructor
	// as the scope ends and e is destroyed, the destructor is called and executed

	{
		// declaring example instance on the heap
		// this instance is not bound to this scope/block since has a permanent address on the heap
		//Example* e_ptr = new Example();
	}
	// when the above scope ends, e_ptr will not be destroyed and the destructor will not be called 

	{
		ScopedPointer s_ptr(new Example()); // implicit conversion. we have a ScopedPointer constructor which takes in an Example instance.
		// this is the basic idea of smart pointers
		// s_ptr itself is initialized on the stack, but passes a pointer of Example which is stored on the heap to the constructor
		// when the scope ends, s_ptr goes out of scope, is destroyed and its destructor which in turn deletes the pointer to the Example instance which
		// is stored on the heap. This helps to automated the deletion of objects/instances stored on the heap and their cleanup is simplified
	}
}