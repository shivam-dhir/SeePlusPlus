#include <iostream>
#include <vector>

void printValue(int value1, int value2) {
	std::cout << value1 << std::endl;
}

// makes the values in the vector double their original value
void changeValue(std::vector<int>& vec) {
	// makes the values in the vector double their original value
	for (int &i : vec)
		i *= 2;

	// does not modify the original vector
	for (int i : vec)
		i *= 2;
}

// the printValue function is captured by the function pointer ptrFunc
void pointerFunction(std::vector<int> vec, void (*ptrFunc)(int, int)) {
	for(int i : vec){
		ptrFunc(i, i); // call the function using the function
	}
}

int main() {
	std::vector<int> arr = { 1,2,3,4,5 };
	//changeValue(arr);

	// sending function as a pointer
	pointerFunction(arr, printValue);

	// exactly the same behavior as above but using a lambda function
	pointerFunction(arr, [](int value1, int value2) {std::cout << value1 << std::endl; });
}