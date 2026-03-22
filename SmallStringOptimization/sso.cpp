#include <iostream>
#include <chrono>
#include "SmallString.h"

class Timer {

private:
	std::chrono::high_resolution_clock::time_point start_time; // Variable to store the start time of the timer
	public:
	Timer() {
		start_time = std::chrono::high_resolution_clock::now(); // Record the start time when the Timer object is created
	}
	~Timer() {
		auto end_time = std::chrono::high_resolution_clock::now(); // Record the end time when the Timer object is destroyed
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count(); // Calculate the duration in milliseconds
		std::cout << "Duration: " << duration << " ms" << std::endl; // Print the duration to the console
	}
};

int main() {
	String s1("abc");
	//std::cout << "s1: " << s1.c_str() << ", size: " << s1.length() << std::endl;

	//s1.reserve(20);

	//std::cout << "push_back\n";
	//s1.push_back('d');
	//std::cout << s1.c_str() << std::endl;

	//std::cout << "append\n";
	//s1.append(" efgh");
	//std::cout << s1.c_str() << std::endl;
	
	String s2("abcdefhghsfddfsdfsdfsdfsdfsdfe1wewzcdvsfd");
	int N = 10000000;
	{
		Timer timer; // Start the timer for this block of code
		for (int i = 0; i < N; ++i) {
			s2.push_back('a'); // Create a new String object in each iteration
		}
	} // The timer will automatically stop and print the duration when it goes out of scope

	return 0;
}