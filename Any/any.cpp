#include <iostream>
#include <any>

int main() {

	std::any data;
	data = 2;
	std::cout << data.type().name() << std::endl;

	data = "hello";
	std::cout << data.type().name() << std::endl;

	data = std::string("nigger");
	std::cout << data.type().name() << std::endl;

}