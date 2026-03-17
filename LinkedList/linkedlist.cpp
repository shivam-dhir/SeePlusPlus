#include <iostream>
#include "Linked.h"

int main() {
	Linked<int> list;
	list.addNode(10);
	list.addNode(20);
	list.addNode(30);

	list.print();

}