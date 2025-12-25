#include <iostream>
#include <cstring> // for strlen and memcpy

struct Example {
	int x, y;
};

class String {
private:
	char* m_Buffer;
	// unsigned since size cannot be negative
	unsigned int m_Size;


public:

	int* m_x;

	// Copy Constructor
	// default copy constructor provided by c++ does a shallow copy
	// copy constructors are used to create a new object as a copy of an existing object, to avoid the shallow copy problem we need to implement our own copy constructor
	// shallow copy means that when an object is copied, the member variables that are pointers are copied as is, meaning both objects point to the same memory address
	// when one object is destroyed, the memory is freed, leaving the other object with a dangling pointer
	// copy constructor syntax: ClassName(const ClassName& other). the class instance passed as a parameter is passed by reference to avoid infinite recursion
	String(const String& other) : m_Size(other.m_Size){
		
		std::cout << "Copy instance created" << std::endl;

		// shallow copy implementation
		/*memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
		memcpy(m_x, other.m_x, 8);*/

		// shallow copy implementation
		// copies the contents of other.m_Buffer into a new memory address, i.e. this->m_Buffer
		// memcpy just copies the bytes from one memory location to another
		// in this case, the m_Buffer and m_x pointers of other are copied into this object's m_Buffer and m_x pointers
		// they will still point to the same memory address as other.m_Buffer and other.m_x
		// only the pointers are copied, not the contents they point to, thats why we need to do a deep copy
		//memcpy(this, &other, sizeof other);

		m_Buffer = new char[m_Size + 1];
		m_x = new int(*other.m_x);
		// first creating a new memory location for m_Buffer and m_x, then copying the contents from other.m_Buffer and other.m_x into the newly allocated memory using memcpy
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
	}

	// when we want to prevent copying of an object, we can delete the copy constructor
	String(const String& other) = delete; // delete copy constructor to prevent copying of the object

	// string literals are not allowed to be modified in c++, that's why we need const char* as a parameter
	String(const char* string, int* x) {

		m_x = x;

		m_Size = strlen(string);

		// it should be m_Size + 1 to copy the null terminator, this is just for learning purpose
		m_Buffer = new char[m_Size + 1];

		// copying contents from string to m_Buffer
		/*for (int i = 0; i < m_Size; i++) {
			m_Buffer[i] = string[i];
		}*/

		// manually allocate the null terminator. another method to do add null terminator
		m_Buffer[m_Size] = 0;


		// memcopy does the same thing as the above for loop
		// strcpy copies the null terminator itself
		memcpy(m_Buffer, string, m_Size + 1);

	}

	~String() {
		// deleteing m_Buffer to avoid memory leak
		delete[] m_Buffer;

		delete m_x;
	}

	// friend functions can access private members outside the class
	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string) {
	stream << string.m_Buffer;
	return stream;
}

void printStringByValue(String string) {}

void printStringByReference(const String& string) {}

int main() {
	Example e1(1, 2);

	// both e1 and e2 are separate objects with different memory addresses. e2 just copies the values of e1's members.
	Example e2 = e1;

	// both e3 and e4 point to the same memory address. they are not separate instances. e4 is just another name for the same object as e3.
	Example* e3 = new Example(1, 2);
	Example* e4 = e3;

	e4 -> x = 10; // modifying e4 also affects e3 since they point to the same object

	// 
	String string("Shimpy", new int(5));
	std::cout << string << std::endl;

	// this is a shallow copy. all the member of string are copied into second. The m_Buffer & m_x pointers are also copied into second, which means there
	// are 2 pointers which point to the same memory address of "Shimpy".
	// after both the objects string and second are destroyed as they go out of scope, the destructor for both of them is called which deletes
	// m_Buffer twice, which causes a crash
	String second = string;
	std::cout << second << std::endl;

	// dereferencing both pointers to show they point to the same memory address
	// both the objects string and second have their own m_x pointer, but both pointers point to the same memory address, since we did a shallow copy
	*(string.m_x) = 98;

	std::cout << "second.x: " << *(second.m_x) << std::endl;
	std::cout << "string.x: " << *(string.m_x) << std::endl;

	//std::cout << "string.m_Buffer" << *(string.m_Buffer) << std::endl;
	//std::cout << "second.m_Buffer" << *(second.m_Buffer) << std::endl;


	// since we have defined a copy constructor, when we pass string by value to printString function, a new copy of string is created using the copy constructor
	// if we hadn't defined a copy constructor, the default copy constructor would have been used which does a shallow copy
	// it is good practice to define a copy constructor when your class manages resources like dynamic memory
	// it is good practice to pass objects by reference to avoid unnecessary copies
	printStringByValue(string);
	printStringByValue(second);

	printStringByReference(string);
	printStringByReference(second);

	std::cin.get();
}