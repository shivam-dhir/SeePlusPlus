// namespaces are used to avoid name conflicts in large projects by grouping related code together.
// different libraries or modules might define functions with the same name, leading to ambiguity.
// std is the standard namespace in C++ that contains all the standard library functions and objects.
// By using namespaces, we can ensure that our code remains organized and free from naming collisions.

// we should avoid 'using namespace' directives in header files to prevent namespace pollution and potential name conflicts in files that include those headers.
// because it can lead to ambiguity and make the code harder to read and maintain.
// Eg: many livraries define a function named 'add', using 'using namespace' could lead to conflicts if multiple libraries are included.

#include <iostream>

namespace Math {
	void add(int a, int b) {
		std::cout << a + b << std::endl;
	}
	void subtract(int a, int b) {
		std::cout << a - b << std::endl;
	}
}

namespace Physics {
	void add(int a, int b) {
		std::cout << a + b << std::endl;
	}
	void subtract(int a, int b) {
		std::cout << a - b << std::endl;
	}
}

namespace Chemistry {

	// nested namespace
	namespace function {

		void add(int a, int b) {
			std::cout << a + b << std::endl;
		}
		void subtract(int a, int b) {
			std::cout << a - b << std::endl;
		}
	}
}

int main() {

	Math::add(10, 30);
	Physics::add(20, 50);

	{
		using namespace Math;
		subtract(50, 20); // Calls Math::subtract
		// using namespace globally here is generally discouraged
		// it can lead to ambiguity if multiple namespaces have functions with the same name
		// try to keep using namespace directives limited in scope
	}

	{
		// p is only an alias within this block
		// it is not accessible outside this block
		namespace p = Physics;
		p::subtract(80, 30); // Calls Physics::subtract
	}

	{
		using namespace Chemistry::function;
		add(5, 15); // Calls Chemistry::function::add
	}

	{
		namespace c_f = Chemistry::function;
		c_f::add(44, 97);
	}

}
