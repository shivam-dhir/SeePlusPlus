// const can be bypassed with pointers and casting

// RULE:
// For pointers, read the declaration from right to left
// Eg: const int* var; means var is a pointer to an int that is const (cannot be changed through this pointer)
// Eg: int* const var; means var is a const pointer to an int (cannot change where it points to)
// Eg: const int* const var; means var is a const pointer to a const int (cannot change either the value or the address)

#include <iostream>

class Entity {

private:
		int m_x = 5;
		int* m_y;

		int* m_z, m_1; // m_z is a pointer to an int, m_1 is just an int
		int m_2, * m_3, * m_4; // m_2 is an int, m_3 and m_4 are pointers to int

		mutable int var = 13;

public:

	// getter
	// const at the end means this function does not modify any member variables of the class
	// also it does not allow inherited classes to modify member variables
	int getX() const {
		// this would be invalid if var was not declared as mutable
		var = 15; // valid, because var is declared as mutable
		return m_x;
	}
	
	// the function return a const pointer to a const int, which means the caller cannot modify the value pointed to nor change where the pointer points to 
	// also the function itself does not modify any member variables of the class, due to the const at the end
	const int* const getY() const {
		return m_y;
	}

	// setter
	// this function modifies member variables, so no const at the end
	void setX(int x) {
		m_x = x;
	}
};

void printEntity(Entity* e) {
	std::cout << e -> getX() << std::endl;
}

// e is a const reference to an Entity object, i.e., we cannot modify the Entity object through this reference although we can change where the reference points to
void printEntityConst(const Entity& e) {
	// e -> setX(10); // error: cannot call non-const member function 'setX' on a const object
	// since the reference is const, we cannot modify the Entity object through this reference,
	// therefore the function also needs to be const to ensure it does not modify any member variables of the class
	std::cout << e.getX() << std::endl;
}


void constPrecedence() {

	// const before and after the asterisk have different meanings, as shown below:

	const int* var = new int(76); // we cannot change the value of var through this pointer
	//*var = 10; // error: read-only variable is not assignable
	// we can change where var points to though, but no modification of the value it points to

	int* x = new int(67);

	int* const var2 = new int(82); // we can change the value of var2 through this pointer, but cannot change where it points to
	//*var2 = 90; // valid
	//var2 = &x;  error: cannot assign to variable 'var2' with const-qualified type 'int *const'

	const int* const var3 = new int(45); // we cannot change the value of var3 through this pointer, nor can we change where it points to
	// we have const both before and after the asterisk, so we cannot change either the value or the address
}

void bypassConstPointer() {

	int* x = new int;
	*x = 5;
	std::cout << *x << std::endl;

	const int var = 10;

	// cannot do this: x = &var; // error: cannot convert from 'const int *' to 'int *'
	// var is of type const int, so &var is of type const int*
	//x = &var;	
	
	// we cannot assign a pointer to a const int beacuse int* means the pointer should point to something that is writeable,
	// but var is const, so it is not writeable, which is why the compiler throws an error

	x = (int*)&var; // cast away const-ness, very dangerous, undefined behavior, because var is stored in read-only memory
}

void constFunctionCheck() {
	// new keyword dynamically allocates memory on the heap
	const int* var = new int;
	const int x = 11;
	std::cout << x << std::endl;
	//delete var;
}

int main() {
	//constFunctionCheck();
	//bypassConstPointer();
	Entity* e = new Entity(); // new keyword dynamically allocates memory on the heap and returns a pointer to the allocated memory
	printEntity(e);

	printEntityConst(*e); // dereference the pointer to get the object
}