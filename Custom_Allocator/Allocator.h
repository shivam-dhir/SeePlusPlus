#include <cstddef>
#include <new>

class Arena {
private:
	std::byte* memory;
	std::size_t size;
	std::size_t offset;

public:
	Arena(std::size_t size) {
		memory = static_cast<std::byte*>(std::malloc(size));
		if (!memory) {
			throw std::bad_alloc();
		}
		this->size = size;
		offset = 0;
	}

	// Move constructor to allow moving Arena instances without copying
	Arena(Arena&& other) noexcept
		: memory(other.memory), size(other.size), offset(other.offset) {
		other.memory = nullptr;
		other.size = 0;
		other.offset = 0;
	}

	// Move assignment operator to allow moving Arena instances without copying
	// returning by reference to support chaining of move assignments
	Arena& operator=(Arena&& other) noexcept {

		if (this == &other) {
			return *this; // Handle self-assignment
		}

		std::free(memory); // Free existing memory before taking ownership of the new one

		memory = other.memory;
		size = other.size;
		offset = other.offset;

		other.memory = nullptr;
		other.size = 0;
		other.offset = 0;

		return *this;
	}

	// Delete copy constructor and assignment operator to prevent copying
	// Arena instances should not be copyable to avoid double-free issues
	Arena(const Arena&) = delete;
	Arena& operator=(const Arena&) = delete;

	~Arena() {
		std::free(memory);
	}

	// returning void* to allow for generic memory allocation, similar to malloc
	// can easily be used to allocate memory for any type, and the caller can cast it to the appropriate type
	void* allocate(std::size_t bytes) {
		if (offset + bytes > size) {
			throw std::bad_alloc();
		}

		std::byte* ptr = memory + offset;
		offset += bytes;
		return static_cast<void*>(ptr);
	}

	void reset() noexcept {
		offset = 0;
	}

	std::size_t used() const noexcept {
		return offset;
	}

	std::size_t capacity() const noexcept {
		return size;
	}

	std::size_t remaining() const noexcept {
		return size - offset;
	}

	// Template method to create an object of type T in the arena
	// This method will be accesedsed by the user to create objects of any type, and it will handle the memory allocation and object construction in one step
	template<typename T, typename... Args>
	T* create(Args&&... args) {
		void* ptr = allocate(sizeof(T));
		return new (ptr) T(std::forward<Args>(args)...);
	}

	template<typename T>
	void destroy(T* ptr) {
		// Call the destructor explicitly since we are managing memory manually
		// Note: This does not free the memory, it just calls the destructor. The memory will be freed when the Arena is destroyed or reset.
		if (ptr) {
			ptr->~T();
		}
	}
};
