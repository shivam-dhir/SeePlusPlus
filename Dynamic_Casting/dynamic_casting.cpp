#include <iostream>

class Entity {
	// creating virtual function to make this a polymorphic class
	virtual void print();
};

// Inheritence creates a 'is-a' relationship
// Basically, Player is a Entity, but Entity is NOT a Player
// Writing private before inherited class name means, public members of Entity will not be accessible through mehtods of Player
class Player : public Entity {
	void print() {

	}
};

class Enemy : public Entity{

};

int main() {

	// player has 2 types: player itself and entity
	Player* player = new Player();
	// Implicit Casting
	Entity* e = player;

	// Player* p = e; e is of type Entity, can't be assigned to Player*

	Entity* enemy = new Enemy();

	// This code works, but is VERY DANGEROUS.
	// enemy is an Enemy instance, and we have cast it to Player*
	// This can lead to undefined behaviour. 
	// Eg: Enemy may have certain methods, member not present in Player class.
	// Trying to access them through a Player* pointer can lead to undefined behaviour or even program crash
	Player* p1 = (Player*)enemy;

	// Above happens because the compiler doesn't know if enemy is of type Player or Enemy
	// Casting it to Player assures the compiler that it is a Player, even though it is not

	// To avoid this problem, we can use dynamic_cast, which checks if the conversion is allowed.
	// If not, it returns a null pointer

	//  the operand of a pointer dynamic_cast in C++ must be a polymorphic class type
	//  The dynamic_cast operator is specifically designed to perform runtime checks for safe downcasting within an inheritance hierarchy. It needs the presence of a virtual function table (vtable), which is how C++ manages runtime type information (RTTI), to determine the actual type of the object the pointer points to at the time the cast is executed
	// This only happends when the class has at least one virtual function
	// This enables runtime polymorphism
	// This is important because, when destructor of derived class is called, destructor of Base must also be called for safe closure of program and preventing memory leaks
	Player* pCheck = dynamic_cast<Player*>(enemy);

	if (pCheck)
		std::cout << "Dynamic Casting worked" << std::endl;
	else std::cout << "Dynamic Casting didn't work" << std::endl;

	// C++ stores RTTI (Run time type information), which is basically information about type of variables 
	// This helps dynamic cast to determine if the conversion is possible
	// disabling this would crash the program if dynamic casting is not allowed
}