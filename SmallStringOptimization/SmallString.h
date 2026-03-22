#pragma once

#include <cstring>

class String {
private:
	// capacity: the total allocated memory for the string (including null terminator)
	size_t capacity;
	// size: the actual length of the string (excluding null terminator)
	size_t size;
	// data: pointer to the character array that holds the string content
	char* data;

public:
	String() : capacity(0), size(0), data(nullptr) {}

	explicit String(const char* str) {
		size = strlen(str);
		capacity = size + 1; // +1 for null terminator
		data = new char[capacity];
		memcpy(data, str, capacity); // Copy the input string into the allocated memory
	}

	// Copy constructor
	String(const String& other): capacity(other.capacity), size(other.size) {
		data = new char[capacity]; // Allocate new memory for the string content
		std::memcpy(data, other.data, capacity); // Copy the string content from the other String object
	}

	// Move constructor
	// noexcept is used to indicate that this constructor does not throw exceptions, which allows for certain optimizations
	// if noexcept is not specified, copy operations may be used instead of move operations, which can lead to less efficient code
	String(String&& other) noexcept: capacity(other.capacity), size(other.size), data(other.data) {
		other.data = nullptr; // Set the other String's data pointer to nullptr to avoid double deletion
		other.size = 0; // Reset the other String's size to 0
		other.capacity = 0; // Reset the other String's capacity to 0
	}

	~String() {
		delete[] data;
	}

	const char* c_str() const {
		return data; // Return a pointer to the string content
	}

	size_t length() const {
		return size; // Return the length of the string
	}

	void reserve(size_t new_capacity) {
		if (capacity >= new_capacity)
			return; // No need to reserve if the current capacity is sufficient

		char* new_data = new char[new_capacity]; // Allocate new memory with the new 

		if(data)
			std::memcpy(new_data, data, size + 1); // Copy the existing string content to the new memory
		
		delete[] data; // Free the old memory
		data = new_data; // Update the data pointer to the new memory
		capacity = new_capacity; // Update the capacity to the new value
	}

	void push_back(char c) {
		if (size + 1 >= capacity) {
			reserve(capacity == 0 ? 1 : capacity * 2); // Double the capacity if needed
		}

		data[size++] = c; // Add the new character to the end of the string
		data[size] = '\0'; // Null-terminate the string
	}

	void append(const char* str) {
		size_t str_length = strlen(str);
		if(size + str_length + 1 > capacity) {
			reserve(size + str_length + 1); // Ensure there is enough capacity for the new string
		}

		std::memcpy(data + size, str, str_length); // Append the new string content to the existing string
		data[size + str_length] = '\0'; // Null-terminate the string
		size += str_length; // Update the size to reflect the new length of the string
	}
};
