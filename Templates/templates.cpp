// Templates are similar to Generics in java or C#, but much more powerful and flexible.
// Templates allow you to write code that works with any data type, enabling code reuse and type safety.

#include <iostream>

// templates are evfaluated at compile time, so we can use them to define data structures with fixed sizes.
// in this case, we need the size of the array to be known at compile time.
// we can do this be defining a template that takes an integer parameter representing the size of the array.
// to initalize an instance of this class, we need to provide a template argument representing the size of the array.
// T can be any data type, and N must be a constant expression known at compile time.
template<typename T, int N> class Array {
private:
	T m_Array[N];

public:
	int getSize() const {
		return N;
	}
};

// Templates are not defined at runtime, but at compile time.
// Eg: when you call print(23), the compiler generates a version of print specifically for int, similarly for other types.
// So, the function is called with a particular type, the compiler generates the appropriate code for that type.
// If the function is never called, the compiler does not generate code for that type.
template<typename T> void print(T var) {
	std::cout << "var: " << var << std::endl;
}

int main() {
	/*print(23);
	print("hello");
	print(4.6f);*/

	// 5 here is a template argument, which is a constant expression known at compile time.
	// So, the compiler generates a version of Array specifically for int and size 5.
	// int is the type parameter, and 5 is the non-type parameter.
	Array<int, 5> arr;
	std::cout << arr.getSize() << std::endl;	
}