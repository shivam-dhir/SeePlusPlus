#include <iostream>
#include <thread>

static bool flag = true;

void doWork() {

	std::cout << "Worker thread ID: " << std::this_thread::get_id() << std::endl;
	
	while (flag) {
		std::cout << "Thread Working ..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

}

int main() {

	std::cout << "Main thread ID: " << std::this_thread::get_id() << std::endl;

	// keeps working until user hits enter
	std::thread worker(doWork);

	std::cin.get();
	
	// on pressing enter at anytime, flag will be set to false which terminates the worker thread
	flag = false;

	// wait for the worker thread to finish
	worker.join();

	std::cout << "Worker thread has finished execution." << std::endl;

	std::cin.get();
}