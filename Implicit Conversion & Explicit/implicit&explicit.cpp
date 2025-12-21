#include <iostream>

class Example {

private:
	int m_x;
	std::string m_str;

public:

	Example(int x): m_x(x) {
		std::cout << "implicit conversion" << std::endl;
	}

	Example(std::string str): m_str(str){}

	Example(int x, std::string str)
		: m_str(str), m_x(x){
		std::cout << "number: " << m_x << std::endl;
		std::cout << "string: " << m_str << std::endl;
	}

	// specifying explicit prevents implicit conversions
	// to use this constructor, the user must explicitly create an Example object or use direct initialization
	explicit Example(int x, std::string str) : m_x(x), m_str(str) {}

};

void printExample(const Example& example) {
	// Function body can be implemented as needed
}

int main() {
	std::string str = "nigger";
	int x = 79;
	//Example a(x, str);

	Example b = 87; // implicit conversion

	//Example c = "hello"; // invalid, because "hello" is not a std::string, but const char*

	printExample(99); // 99 is implicitly converted to Example(99), since Example has a constructor that takes an int
	printExample(std::string("world")); // "world" is implicitly converted to Example(std::string("world"))
	printExample(Example(42, "example")); // Explicitly creating an Example object
}