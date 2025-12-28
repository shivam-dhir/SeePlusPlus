#include <iostream>
#include <vector>

class Vector {
public:
	float x, y, z;

	// constructor
	Vector(int x, int y, int z): 
		x(x), y(y), z(z) {}

	//Copy Constructor
	Vector(const Vector& vector):
		x(vector.x), y(vector.y), z(vector.z){
		std::cout << "copied\n";
	}
};


// Overloading the << operator for Vector class
// std::cout is an instance of std::ostream, which is used for output operations in C++, so we define the operator to take a reference to std::ostream and a reference to Vector.
// std::ostream& parameter must be non-const because we are modifying the stream by inserting data into it.
// Never pass std::ostream by value — streams are non-copyable.
std::ostream& operator<<(std::ostream& stream, const Vector& vector) {
	stream << "x: " << vector.x << ", y: " << vector.y << ", z: " << vector.z;
	return stream;
}

int main() {
	Vector vec(1, 2, 3);
	//std::cout << vec << std::endl;

	std::vector<Vector> vector;
	vector.push_back(Vector(1, 2, 3));
	vector.push_back({ 4, 5, 6 }); // implicit construction, equivalen to vector.push_back(Vector{4, 5, 6});
	vector.push_back(Vector(7, 8, 91));

	// Unlike Java, C++ has overloaded the [] operator for std::vector to provide direct access to its elements.
	for(int i=0;i<vector.size();i++)
		std::cout << vector[i] << std::endl;
	
	// Range-based for loop
	// In this case, we are copying each Vector from the vector to the variable v.
	// If we wanted to avoid the copy, we could use a reference: for (Vector& v : vector)
	for (Vector v : vector)
		std::cout << v << std::endl;

	for(Vector& v : vector) // using reference to avoid copying
		std::cout << v << std::endl;

	// erase function does not take in an index, it needs an iterator which points to that particular index
	int index = 1;
	vector.erase(vector.begin() + index);

	vector.clear(); // clear the vector, set size to 0

	//---------------------------------------------------------------------------------------------------------

	std::vector<Vector> vectorArray;
	// Optimization
	// there are two choke points in the code above:
	// 1. whenever we push back an element in vector array, it allocates memory greater than current size in a new address
	//    and then copies all the data to the new address
	// 2. When we push_back an element into the vector array, an object is first created in the stack of main function,
	//	  and then placed into the address where vector array lives. This leads to multiple unnecessary copies being made

	// 1. To solve the first issue of vector allocating new memory everytime, we can allocate some memory at compile time
	// so it does not have to reallocate for every push_back

	vectorArray.reserve(5); // the number 5 here means enough memory to store 5 instances of Vector objects
	// allocating sufficient memory at compile time helps to not copy data multiple times
	vectorArray.push_back(Vector(1, 2, 3));
	vectorArray.push_back(Vector(2, 3, 4));
	vectorArray.push_back(Vector(5, 6, 7));

	// 2. To solve the issue of first creating objects inside current scope and then placing it in the vector, which results in copying
	//    we can use emplace_back which creates the objects at the address where vector array lives. so there is no need to copy and delete extra objects

	// to use emplace_back, we only need to pass in the parameter list for the constructor, which creates a Vector object in place
	vectorArray.emplace_back(1, 2, 3);
	vectorArray.emplace_back(3, 4, 5);
	vectorArray.emplace_back(7, 8, 9);

}