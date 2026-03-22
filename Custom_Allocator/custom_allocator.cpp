#include <iostream>
#include <cstddef>
#include <cstdlib>
#include "Allocator.h"

struct Entity {
	int id;
	float x, y;

	Entity(int id, float x, float y) : id(id), x(x), y(y) {}
};

int main() {
	Arena arena(100 * sizeof(Entity)); // Create an arena with 100 instances of Entity
	Entity* e1 = arena.create<Entity>(1, 10.0f, 20.0f); // Create an Entity in the arena
	std::cout << arena.used() << " bytes used, " << arena.remaining() << " bytes remaining." << std::endl;
	Entity* e2 = arena.create<Entity>(3, 40.0f, 50.0f); // Create an Entity in the arena
	std::cout << arena.used() << " bytes used, " << arena.remaining() << " bytes remaining." << std::endl;

	arena.destroy(e1); // Destroy the first Entity
	std::cout << arena.used() << " bytes used, " << arena.remaining() << " bytes remaining." << std::endl;
	arena.destroy(e2); // Destroy the second Entity

	arena.reset(); // Reset the arena to reuse memory
}
