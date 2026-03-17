#pragma once
#include <iostream>

template <typename T>
class Linked {

	Linked* head;
	Linked* tail;
	Linked* next;
	Linked* prev;
	T value;

public:
	Linked() {
		head = new Linked();
		tail = new Linked();
		head->next = tail;
		tail->prev = head;
	}
	~Linked() {
		while (head != nullptr) {
			Linked* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void addNode(T value) {
		Linked* node = new Linked();
		node->value = value;
		node->prev = tail->prev;
		node->next = tail;
		tail->prev->next = node;
		tail->prev = node;
	}

	void removeNode(T value) {
		Linked* current = head->next;
		while (current != tail) {
			if (current->value == value) {
				current->prev->next = current->next;
				current->next->prev = current->prev;
				delete current;
				return;
			}
			current = current->next;
		}
	}

	void print() {
		Linked* current = head->next;
		while (current != tail) {
			std::cout << current->value << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}
};


// End of Linked.h