#include <iostream>

class Singleton {
private:
	//static  Singleton* singleton;

public:

	/*static Singleton& getSingleton() {
		return *singleton;
	}*/

	// we can use static to create a singleton class, ensuring that only one instance of the class exists throughout the program's lifetime.
	static Singleton& getInstance() {
		// instead of creating a private static member variable, we can use a local static variable inside the getInstance() method. For every function call, this instance will be created only once.
		// By using static, we increase the lifetime of the instance to the entire program duration.
		static Singleton instance; // Guaranteed to be destroyed and instantiated on first use.
		return instance;
	}
};

void function() {

	// counter is a regular local variable, so it is reinitialized to 0 every time the function is called.
	int counter = 0;
	counter++;

	// since count is static, it retains its value between function calls. Every time the function is called, count is incremented by 1 and printed, and not reinitialized to 0.
	static int count = 0;
	count++;
	std::cout << "count: " << count << std::endl;
	std::cout << "counter: " << counter << std::endl;
}

int main() {
	function();
	function();
	function();
	function();
	function();
}