#include "vector.h"
#include <iostream>
#include <chrono>

class Entity {

private:
	int x=0, y=0;

public:

	Entity() = default;

	Entity(int x, int y) : x(x), y(y) {
		//std::cout << "Default constructor called" << std::endl;
	}

	Entity(const Entity& other): x(other.x), y(other.y) {
		//std::cout << "Copy constructor called" << std::endl;
	}

	Entity(Entity&& other) noexcept : x(other.x), y(other.y) {
		//std::cout << "Move constructor called" << std::endl;
	}

	Entity& operator=(const Entity& other) noexcept {
		// std::cout << "Copy assignment operator called" << std::endl;
		if (this == &other) return *this;
		x = other.x;
		y = other.y;
		return *this;
	}

	Entity& operator=(Entity&& other) noexcept {
		// std::cout << "Move assignment operator called" << std::endl;
		if (this == &other) return *this;
		x = other.x;
		y = other.y;
		return *this;
	}
};

class Timer {

private:
	std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
public:
	Timer() {
		start_time = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
		std::cout << "Duration: " << duration << " ms" << std::endl;	
	}

};

int main() {
	Vector<Entity> entities;
	Vector<Entity> entities2;

	std::cout << "No reserve" << std::endl;	

	{
		Timer timer;
		for (int i = 0; i < 1000000; ++i) {
			entities.push_back(Entity(i, i));
		}
	}

	std::cout << "With reserve" << std::endl;
	entities2.reserve(100000);
	{
		Timer timer;
		for (int i = 0; i < 100000; ++i) {
			entities2.push_back(Entity(i, i));
		}
	}
	
	return 0;
}