#include <iostream>
#include <cstring>

class Vector {

private:
	int* m_data;
	int m_size;
	int m_count = 0;

	int* provisionMemory(int size) {
		return new int[size];
	}

public:
	Vector() {
		m_size = 10;
		m_data = provisionMemory(m_size);
	}

	Vector(int size) {
		m_size = size;
		m_data = provisionMemory(m_size);
		memset(m_data, 0, m_size * sizeof(int));
	}

	int size() const {
		return m_size;
	}

	void add(int value) {
		if (m_count == m_size) {
			std::cout << "Allocating new block of memory ... \n";
			int* new_data = provisionMemory(m_size * 2);
			m_size *= 2;
			memcpy(new_data, m_data, m_size / 2 * sizeof(int));
			delete[] m_data;
			m_data = new_data;
		}
		m_data[m_count] = value;
		std::cout << "Added: " << m_data[m_count] << std::endl;
		m_count++;
	}

	void remove() {
		if (m_count == 0) {
			std::cout << "Vector is empty!" << std::endl;
			return;
		}
		m_count--;
	}

	int operator[](int index) {
		return m_data[index];
	}
};

int main() {
	Vector vector(3);
	vector.add(1);	
	vector.add(2);
	vector.add(3);
	vector.add(4);
	vector.add(5);
	vector.add(6);

	//int* data = vector.getData();
	for (int i = 0; i < vector.size(); i++) {
		std::cout << "Element " << i << ": " << vector[i] << std::endl;
	}

	//std::cout << "First Element: " << data[0] << std::endl; // Outputs: 1
}