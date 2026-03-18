#include <utility>
#include <iostream>
#include <new>

template <typename T>
class Vector {
private:
	T* data;
	size_t size = 0;
	size_t capacity;

public:

    Vector() {
        capacity = 1;
        data = static_cast<T*>(operator new[](capacity * sizeof(T)));
    }

    Vector(int init_capacity) : capacity(init_capacity) {
        data = static_cast<T*>(operator new[](capacity * sizeof(T)));
    }

    ~Vector() {
        for (size_t i = 0; i < size; ++i) {
            data[i].~T();
        }
        operator delete[](data);
    }

	T& operator[](int index) {
		return data[index];
	}

	const T& operator[](int index) const {
		return data[index];
	}

	void push_back(const T& value) {
		// Implementation for adding an element to the end of the vector
        if(size >= capacity)
            grow();
        new (data + size) T(value);
        ++size;
	}

	void push_back(T&& value) {
		// Implementation for adding an element to the end of the vector using move semantics
        if (size >= capacity)
            grow();
        //std::cout << "Move push_back called \n";
        new (data + size) T(std::move(value));
        ++size;
	}

    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity) return;

        T* newData = static_cast<T*>(operator new[](new_capacity * sizeof(T)));

        for (size_t i = 0; i < size; ++i) {
            new (newData + i) T(std::move_if_noexcept(data[i]));
            data[i].~T();
        }

        operator delete[](data);

        data = newData;
        capacity = new_capacity;
    }

	size_t current_size() const {
		return size;
	}

	void grow() {
		if (size >= capacity) {
			//std::cout << "Capacity Increase \n";
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = static_cast<T*>(operator new[](capacity * sizeof(T)));
            for (size_t i = 0; i < size; i++) {
                new (newData + i) T(std::move(data[i]));
                data[i].~T();
            }
            operator delete[](data);
            data = newData;
		}
	}
};