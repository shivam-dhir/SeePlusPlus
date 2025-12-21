//If you do not define a constructor, C++ generates a default one
//But primitive members are NOT automatically initialized unless you do so

#include <iostream>

class Sample {

public:

	Sample() {
		std::cout << "Sample's Constructor Called" << std::endl;
	}

};

class Example {

public:
	Example() {
		std::cout << "Example's constructor called" << std::endl;
	}

	Example(int x) {
		std::cout << "Custom Constructor: " << x << std::endl;
	}
};

class MyClass {

private:
	int m_var;
	std::string m_str;
	Example m_example;
	Sample m_sample;

public:

	// all member variables that have been declared will be initialized whether or not they have been member initialized
	// in this case, m_example and m_sample have not been initialized in the constructor member list
	// but still they are initialized and their default constructors are called
	MyClass(int var, std::string str)
		: m_var(var), m_str(str){
		// if i again try to initialize m_example here, it will be overwriting the previous initialization and the example constructor will be called again
		//m_example = Example(42); // Assignment in body
	}

	// primitive members are not automatically initialized unless we explicitly do so

	// Member Initializer List
	//MyClass(int var, std::string str)
	//	: m_var(var), m_str(str){}

	MyClass(int var) {
		m_var = var;
	}

	MyClass() {
		m_var = 69;
		m_str = "Default Constructor";
	}

	void print() {
		std::cout << "m_var: " << m_var << std::endl;
		std::cout << "m_str: " << m_str << std::endl;
	}
};

int main() {
	//MyClass obj1;
	//obj1.print();

	MyClass obj2(13, "sexy");
	//obj2.print();
}