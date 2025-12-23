struct Example {
	int x, y;
};

int main() {
	Example e1(1, 2);

	// both e1 and e2 are separate objects with different memory addresses. e2 just copies the values of e1's members.
	Example e2 = e1;

	// both e3 and e4 point to the same memory address. they are not separate instances. e4 is just another name for the same object as e3.
	Example* e3 = new Example(1, 2);
	Example* e4 = e3;

	e4->x = 10; // modifying e4 also affects e3 since they point to the same object
}