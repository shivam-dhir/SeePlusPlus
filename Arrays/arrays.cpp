// std:: array objects are stored on the stack and have a fixed size determined at compile time.
// std::vector objects are stored on the heap and can dynamically resize at runtime.

#include <iostream>
#include <array>

void print(std::array<int, 5> arr) {
	for (int i : arr)
		std::cout << i << ", ";
}

void print(int arr[], unsigned int size) {
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << ", ";
}

int main() {
	int arr[5];
	int size = 5;
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 4;
	arr[4] = 5;
	//arr[5] = 6; // This is allowed with C-style arrays, but it causes undefined behavior (out of bounds access), because there is no bounds checking. This will overwrite memory beyond the allocated array.
	//print(arr, size);

	// std::array is stored on the stack
	// std::array class has functions like size(), at(), front(), back(), fill(), etc, which are not available for C-style arrays
	// we can use iterators with std::array, unlike C-style arrays
	// std:: array provides better type safety and avoids decay to pointers
	std::array<int, 5> stdArray = {11, 12, 13, 14, 15};
	print(stdArray);
}
