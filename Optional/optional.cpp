#include <iostream>
#include <fstream>
#include <optional>

// optionals help us to handle cases where we have no data. Eg: a file could not be read, a parameter is missing, a missing resource etc.
// wrapping a string in optional will help us to handle this. 
// no changes in impementation is required. The result is automatically stored in the optional class.
// std::optional is somewhat similar to a smart pointer. 
std::optional<std::string> fileReadBuffer(const std::string& filePath) {
	std::ifstream stream(filePath);

	if (stream) {
		std::string result = "File opened successfully";
		stream.close();
		return result;
	}
	/*else {
		return "File could not be opened ! \n";
	}*/

	// returning an empty optional at the end, just to have a valid std::optional object and a safe return
	return {};
}

int main() {

	//std::string data = fileReadBuffer("data.txt");
	
	std::optional<std::string> data = fileReadBuffer("data1.txt");

	// using value_or with the std::optional, we don't even need a if-else block as commented below
	std::string optional_data = data.value_or("Error: File not found");
	std::cout << optional_data << std::endl;

	//if (data.has_value()) {
	//	std::cout << *data; // std::optional is a smart pointer. To access data, we just need to dereference it.
	//}
	//else std::cout << "Error: File not found !!!\n";

	std::cin.get();
		
}