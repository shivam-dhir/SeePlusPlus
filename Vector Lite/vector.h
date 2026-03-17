#include <utility>
#include <iostream>

template <typename T>
class Vector {
private:
	T* data;
	size_t size = 0;
	size_t capacity;

public:

	Vector() {
		capacity = 1;
		data = new T[capacity];
	}

	Vector(int init_capacity) : capacity(init_capacity) {
		data = new T[capacity];
	}

	~Vector() {
		delete[] data;
	}

	T& operator[](int index) {
		return data[index];
	}

	const T& operator[](int index) const {
		return data[index];
	}

	void push_back(const T& value) {
		// Implementation for adding an element to the end of the vector
		data[size] = value;
		size++;
		resize();
	}

	void push_back(T&& value) {
		// Implementation for adding an element to the end of the vector using move semantics
		std::cout << "Move push_back called \n";
		data[size] = std::move(value);
		size++;
		resize();
	}

	int size_of_vector() const {
		return size;
	}

	void resize() {
		if (size >= capacity) {
			std::cout << "Capacity Increase \n";
			capacity = (capacity == 0) ? 1 : capacity * 2;
			T* newData = new T[capacity];
			for (int i = 0; i < size; i++) {
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}
	}
};