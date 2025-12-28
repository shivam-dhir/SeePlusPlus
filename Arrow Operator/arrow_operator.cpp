#include <iostream>

struct Vector3{
	float x, y, z;
};

class Node {
public:
	int m_Value;

	Node(int value) : m_Value(value) {}

};

int main() {

	Node* node = new Node(57);
	node->m_Value = 67;

	Node node1(54);
	// pointer to the address of node1
	Node* nodePtr = &node1;
	// reference to the object pointed to by nodePtr
	Node& referenceToNode = *nodePtr;

	nodePtr->m_Value = 29;

	//std::cout << nodePtr->m_Value << std::endl;

	// Determining offset of member in structure using arrow operator
	// Vector3 has 3 float members: x, y, z, which are typically 4 bytes each
	// So considering x is at offset 0, y at offset 4, and z at offset 8
	int offsetX = (int) & ((Vector3*) nullptr) -> x;
	int offsetY = (int) & ((Vector3*) nullptr) -> y;
	int offsetZ = (int) & ((Vector3*) nullptr) -> z;
	
	std::cout << offsetX << std::endl;
	std::cout << offsetY << std::endl;
	std::cout << offsetZ << std::endl;
	
	// Alternatively, using offsetof macro from <cstddef>
	std::cout << "Offset of x w.r.t to Vector3: " << offsetof(Vector3, x) << std::endl;
	std::cout << "Offset of y w.r.t to Vector3: " << offsetof(Vector3, y) << std::endl;
	std::cout << "Offset of z w.r.t to Vector3: " << offsetof(Vector3, z) << std::endl;
}