#include <iostream>
#include <cstddef>
#include <cstdlib>

class Arena {
private:
	char* memory;
	std::size_t size;
	std::size_t offset;

public:
	Arena(std::size_t size) {
		memory = new char[size];
		this->size = size;
		offset = 0;
	}

	~Arena() {
		delete[] memory;
	}

	void* allocate(std::size_t bytes) {
		if (offset + bytes > size) {
			throw std::bad_alloc();
		}

		void* ptr = memory + offset;
		offset += bytes;
		return ptr;
	}

	void reset() {
		offset = 0;
	}
};

int main() {

}
