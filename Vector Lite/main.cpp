#include "vector.h"
#include <iostream>

class Entity {

private:
	int x=0, y=0;

public:

	Entity() = default;

	Entity(int x, int y) : x(x), y(y) {
		std::cout << "Default constructor called" << std::endl;
	}

	Entity(const Entity& other) {
		std::cout << "Copy constructor called" << std::endl;
	}

	//Entity(Entity&& other) {
	//	std::cout << "Move constructor called" << std::endl;

	//}
};

int main() {
	Vector<Entity> entities(5);
	entities.push_back(Entity(1,2));
	std::cout << entities.size_of_vector() << std::endl;
	entities.push_back(Entity(2, 3));
	entities.push_back(Entity(3, 4));
	entities.push_back(Entity(4, 5));
	return 0;
}