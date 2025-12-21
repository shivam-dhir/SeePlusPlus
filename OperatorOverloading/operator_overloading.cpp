#include <iostream>

class Vector {
private:
	int x, y;

public:
	Vector(int x, int y) : x(x), y(y) {}

	// operator overloading
	// operator keyword is used to work with operators and overload an existing operator
	// in this case, we are overloading the '==' operator
	bool operator==(Vector& vector) {
		return x == vector.x && y == vector.y;
	}

	// operator overloading
	// operator keyword is used to work with operators and overload an existing operator
	// in this case, we are overloading the '+' operator
	Vector operator+(Vector& vector) {
		return Vector(x + vector.x, y + vector.y);
	}

	static void print(Vector& vector) {
		std::cout << "x: " << vector.x << std::endl;
		std::cout << "y: " << vector.y << std::endl;
	}
};

bool checkEquality(Vector& vec1, Vector& vec2) {
	return vec1 == vec2;
}

int main() {
	Vector vec1 = Vector(1, 3);
	Vector vec2 = Vector(4, 8);

	Vector vec3 = vec1 + vec2;

	Vector::print(vec3);
}