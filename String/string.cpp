#include <iostream>

// when taking in a reference to a char array, size needs to be mentioned so we must know the bounds 
template <std::size_t N>
void referenceToCharArray(char (&reference)[N]) {
	for (int i = 0; i < N; i++)
		std::cout << reference[i];
}

// taking in a copy of the copyString
// any changes to THIS copyString doesn't affect the original copyString from the caller function
void copyClass(std::string copyString) {
	std::cout << copyString << std::endl;

	copyString[2] = 'x';

	for (int i = 0; i < copyString.size(); i++)
		std::cout << copyString[i] << std::endl;
}

// taking in a reference of the refString from the caller function
void stringClass(std::string& refString) {
	std::string str;
	str = "shivam";
	std::cout << "Size: " << str.size() << std::endl;
	std::cout << "Length: " << str.length() << std::endl;
	std::cout << "Reference String: " << refString << std::endl;
}

void charArray() {

	char str[] = {'s', 'e', 'x', 'y', 'y', 'y'};
	for (int i = 0; i < 6; i++) {
		str[i] = str[i] + 1;
		std::cout << str[i] << std::endl;
	}
}

void checkPointer(const char* string) {
	std::cout << string << std::endl;
}

// taking in a pointer to the first character to the stringArray array. 
void checkCharArrayPointer(char* stringArray) {
	for (int i = 0; i < 5; i++)
		std::cout << stringArray[i];
}

// taking in a pointer to the first character of the string literal str
void constCharPointer(const char* str) {
	std::cout << strlen(str) << std::endl;
}

void pointerToInteger(int& ref) {
	std::cout << ref << std::endl;
}

int main() {
	const char* str = "sexyyy";
	//std::cout << str << std::endl;
	//constCharPointer(str);
	//charArray();

	/*int num = 13;
	pointerToInteger(num);*/

	/*const char* string = "hello";
	checkPointer(string);*/


	// stringArray is a poiner which points to the first character of the array
	//char stringArray[] = { 'a', 'b', 'c', 'd', 'e'};
	//checkCharArrayPointer(stringArray);

	/*std::string refString = "This is reference string";
	stringClass(refString);*/

	//copyClass("meowww");

	//  referenceCharArray is an array object, not a pointer. But in most expressions (including when passed to a function that takes a pointer) 
	// it decays to a pointer to the first element. So yes, when you pass the array to a function that takes char* (or const char*), the function receives a pointer that points to the first character.
	char referenceCharArray[] = {'p', 'u', 't', 't', 'W', 'h', 'i', 's', 'k', 'e', 'y'};
	referenceToCharArray(referenceCharArray);
}