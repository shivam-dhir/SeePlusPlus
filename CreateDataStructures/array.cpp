//Constructors ? don’t memset
//Destructors ? don’t memset
//STL types ? never memset

// memset Blindly writes raw bytes
// Has zero awareness of constructors, destructors, pointers, or invariants
// Only safe for trivially copyable / POD - like types

//Safe:
//int
//float
//char
//unsigned char
//struct POD { int x; float y; }

//Unsafe:
//
//std::string
//std::vector
//std::array<std::string, N>
//any class with a constructor or destructor


#include <iostream>
#include <cstring> // for memset

template <typename T, size_t Size>
class Array {
private:
	T* m_Data;
	// template arguments are constant expressions which are known at compile time, so we can use them to define array sizes
	//int m_Array[Size];

	// generic type T
	T m_Array[Size];

public:
	// one way to allocate memory on the stack
	/*Array(int size) {
		m_Data = (int*) alloca(size * sizeof(int));
	}*/

	// constexpr means that the function can be evaluated at compile time
	constexpr size_t size() const {
		return Size;
	}

	// overload the subscript operator, to provide array-like access
	// return reference to reduce copying
	T& operator[](size_t index) {
		return m_Array[index];
	}

	// const version of the subscript operator
	const T& operator[](size_t index) const {
		return m_Array[index];
	}

	T* getData() {
		return &m_Array[0];
	}

	const T* getData() const {
		return &m_Array[0];
	}

};

//int main() {
//
//	//Array arr(5);
//
//	// create an array of 5 integers
//	Array<int, 5> arr;
//
//	// static_assert(arr.Size() < 10, "Too Large");
//	// static_assert can only evaluate constant expressions at compile time
//
//	// set all bytes to 0
//	memset(arr.getData(), 0, arr.size() * sizeof(int));
//
//	arr[0] = 1;
//	arr[3] = 45;
//
//	for (int i = 0; i < arr.size(); i++) {
//		std::cout << arr[i] << " ";
//	}
//
//	std::cout << std::endl;
//
//	Array<std::string, 3> strArr;
//
//	strArr[0] = "Hello";
//	strArr[1] = "World";
//
//	for (int i = 0; i < strArr.size(); i++) {
//		std::cout << strArr[i] << " ";
//	}
//
//}