// variables intialized wiuth auto keyword themselves find their types at compile time based on the assigned value.

#include <iostream>
#include <String>
#include <unordered_map>

//std::string getString() {
//	return "Hello";
//}

// const char* because string literals are of type const char[] and cannot be modified.
const char* getCharPointer() {
	return "Char Pointer";
}
class Example {
private:
	std::string m_String;

public:

	Example(std::string str): m_String(str) {}

	std::string& getString() {
		return m_String;
	}

	std::string getStringCopy() {
		return m_String;
	}
};

std::string getStringReference() {
	return "Reference string";
}

int main() {
	// var will be deduced to be of type int
	auto var = 6;

	//auto str = getString();
	//std::cout << str << std::endl;

	auto charPtr = getCharPointer();
	std::cout << charPtr << std::endl;

	std::vector<std::string> vector;
	vector.push_back("Hello");
	vector.push_back("nigga");
	vector.push_back("blowjob");

	/*for (auto string : vector) {
		std::cout << string << std::endl;
	}*/

	Example e("tamannah bhatia");
	// reference to the string
	auto& str = e.getString();
	std::cout << str << std::endl;

	// copy of the string
	auto strCopy = e.getStringCopy();
	std::cout << strCopy << std::endl;

}