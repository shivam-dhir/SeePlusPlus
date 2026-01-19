#include <iostream>
#include <string_view>

int allocations = 0;


// overloading 'new' operator, just to calculate the number of heap allocations
void* operator new(size_t size) {
	allocations++;
	std::cout << size << " bytes allocated\n";
	return malloc(size);
}

void print(std::string_view str) {
	std::cout << str << std::endl;
}

void print(std::string& str) {
	std::cout << str << std::endl;
}

int main() {

	// std::string does a heap allocation
	//std::string name = "Dodge Charger";
	//print(name);

	// to get rid of even a single allocation, we can use C style strings
	const char* car_name = "Dodge Charger";

# if 0
	// substr first creates a copy of 'name', which again does a heap allocation every time substr is called
	std::string firstName = name.substr(0, 5);
	std::string lastName = name.substr(6);
# else 
	// std::string_view does not lead to any heap_allocation
	// string_view takes in a char* to an arbitrary character of the std::string and a size, which represents a window size
	//std::string_view firstName(name.c_str(), 5);
	// returns pointer to 6th character of name, upto the 12 character
	//std::string_view lastName(name.c_str() + 6, 12);

	// if using C style strings, we don't need to use name.c_str()
	std::string_view firstName1(car_name, 5);
	std::string_view lastName1(car_name + 6, 12);
# endif

	print(firstName1);
	print(lastName1);
	
	std::cout << allocations << " allocations\n";
}