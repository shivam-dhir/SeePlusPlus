#include <iostream>
#include <chrono>

void byValue(std::string s) {

}

void byReference(std::string& s) {

}

void f(int& x) {
    std::cout << "lvalue ref\n";
}

void f(const int& x) {
    std::cout << "const lvalue ref\n";
}

void f(int&& x) {
    std::cout << "rvalue ref\n";
}

int main() {
    int a = 10;
    const int b = 20;
	int million = 1'000'000;    
    std::string str = "comparelargestringperformancebyvalueandreference";

	//f(a); // lvalue ref
	//f(b); // const lvalue ref
	//f(30); // rvalue ref
	//f(a + 5); // rvalue ref

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 1000000; ++i) {
        byValue(str);
    }

	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "Time taken by value: " 
			  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
			  << " ms\n";

	start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 1000000; ++i) {
		byReference(str);
	}

	end = std::chrono::high_resolution_clock::now();

	std::cout << "Time taken by reference: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
		<< " ms\n";

	std::cout << "exit program ..." << std::endl;
}