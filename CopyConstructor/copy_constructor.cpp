#include <iostream>

struct Example {
	int x, y;
};

class String {
private:
	char* m_Buffer;
	// unsigned since size cannot be negative
	unsigned int m_Size;

public:
	// string literals are not allowed to be modified in c++, that's why we need const char* as a parameter
	String(const char* string) {
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
	}

	// friend functions can access private members outside the class
	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string) {
	stream << string.m_Buffer;
	return stream;
}

int main() {
	Example e1(1, 2);

	// both e1 and e2 are separate objects with different memory addresses. e2 just copies the values of e1's members.
	Example e2 = e1;

	// both e3 and e4 point to the same memory address. they are not separate instances. e4 is just another name for the same object as e3.
	Example* e3 = new Example(1, 2);
	Example* e4 = e3;

	e4 -> x = 10; // modifying e4 also affects e3 since they point to the same object

	// 
	String string = "Shimpy";
	std::cout << string << std::endl;

	// this is a shallow copy. all the member of string are copied into second. The m_Buffer pointer is also copied into second, which means there
	// are 2 pointers which point to the same memory address of "Shimpy".
	// after both the objects string and second are destroyed as they go out of scope, the destructor for both of them is called which deletes
	// m_Buffer twice, which causes a crash
	String second = string;
	std::cout << second << std::endl;

	std::cin.get();
}