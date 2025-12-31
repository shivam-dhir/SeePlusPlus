#include <iostream>
#include <chrono>

struct Timer {
	
	std::chrono::time_point<std::chrono::steady_clock> start, end;

	Timer() {
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> duration = end - start;
		std::cout << "duration: " << duration << std::endl;
	}
};

// Method 2: Using RAII Timer class
// This method using object creation and destruction to measure time
// when the Timer object is created, it records the start time
// when the Timer object goes out of scope, its destructor records the end time and calculates the duration
void timingMethod2() {

	Timer timer;

	for(int i = 0; i < 1000; i++);
}

// Method 1: Using chrono library directly
// just get start and end timepoints and calculate duration
void timingMethod1() {

	// Get starting timepoint
	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 100; i++)
		std::cout << i << std::endl;

	// Get ending timepoint
	auto end = std::chrono::high_resolution_clock::now();

	// Stores milliseconds as a double
	std::chrono::duration<double, std::milli> duration = end - start;

	std::cout << "duration: " << duration << std::endl;
}

int main() {
	//timingMethod1();

	timingMethod2();
}