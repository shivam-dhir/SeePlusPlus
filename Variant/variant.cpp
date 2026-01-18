
// Variant can store and represent different types of variables
// Unlike a union, which allocates memory for the largest sized variable in the union, variant allocates memory for all the specified types

#include <iostream>
#include <variant>

enum FileErrorCode {
	None = 0, NotFound = 1, NoAccess = 2, Corrupted = 3
};

// Instead of using optional, which can do just 2 things: return data if it is present and return nothing if no data is present
// we can use variant to return an additional error code like this to specify what kind of error was encountered
std::variant<std::string, FileErrorCode> FileReaderBuffer(const std::string& filePath) {
	return Corrupted;
}

int main() {

	std::variant<std::string, int, float> data;
	data = "hello";

	std::cout << std::get<std::string>(data) << std::endl;

	data = 2;

	std::cout << std::get<int>(data) << std::endl;

	// since data is currently assigned as an 'int', we can't do a std::get<std::string> on data. This leads to a prgram crash
	//::cout << std::get<std::string>(data); // program crashes.

	std::cout << data.index() << std::endl; // this prints out the index of the type 'data' is currently mapped to.
	// 'std::string' is at index 0, 'int' is at index 1 and so on ...


	// std::get_if returns a pointer to the variable if data is mapped to the parameter input of std::get_if, else it returns a null pointer
	// this helps us handle the program crash in the above scenario
	// it takes in a reference to the 'data' variant variable
	auto* val = std::get_if<std::string>(&data);

	data = 3.5f;

	// if the current data in 'data' is a string, we will get a pointer to a valid address, which we can dereference and print it, 
	// else if it returns a null pointer, print a error message
	if (auto value = std::get_if<std::string>(&data)) {
		std::cout << *value << std::endl;
	}
	else std::cout << "Incorrect conversion\n";

	auto result = FileReaderBuffer("data.txt");

	if (auto* str  = std::get_if<std::string>(&result)) {
		std::cout << *str << std::endl;
	}
	if(auto* err = std::get_if<FileErrorCode>(&result)) {
		std::cout << "Error Code: " << *err << std::endl;
	}
}