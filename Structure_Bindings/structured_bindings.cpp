// structured bindings
#include <iostream>
#include <vector>

// a tuple can contain multiple values of different types
std::tuple<std::string, int, std::vector<int>> createTuple() {
	return { "Hello", 13, {1, 2, 3} };
}

int main() {

	auto var = createTuple();

	// std::get<index>(tupleReturn) is used to retrieve the data at index 'index'
	std::string str = std::get<0>(var);
	int num = std::get<1>(var);
	std::vector<int> vec = std::get<2>(var);

	std::string name;
	int number;
	std::vector<int> vector;
	// another way to extract elements out of a tuple
	std::tie(name, number, vector) = createTuple();

	// Structured Binding
	// Only for C++ 17 and newer version
	auto[tupleString, tupleInt, tupleVector] = createTuple();
	std::cout << "tupleString: " << tupleString << std::endl;
	std::cout << "tupleInt: " << tupleInt << std::endl;
	std::cout << "tupleVector: ";
	for (int i : tupleVector)
		std::cout << i << ", ";

}