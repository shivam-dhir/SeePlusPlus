#include <iostream>
#include <unordered_map>
#include <string>
#include <chrono>
#include "flat_hash_map.h"

class Timer {

private:
	std::chrono::high_resolution_clock::time_point start_time;
public:
	Timer() : start_time(std::chrono::high_resolution_clock::now()) {}
	
	~Timer(){
		auto end_time = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration<double>(end_time - start_time).count() << "s" << std::endl;
	}
};

int main() {

	const size_t N = 10000000;

	FlatHashMap<int, int> fmap(N);
	std::unordered_map<int, int> umap(N);

	for (int i = 0; i < N; ++i) {
		fmap.insert(i, i);
		umap[i] = i;
	}

	std::cout << "FlatHashMap: ";
	{
		Timer timer;
		for (int i = 0; i < N; ++i) {
			fmap.get(i);
		}
	}

	std::cout << "std::unordered_map: ";
	{
		Timer timer;
		for (int i = 0; i < N; ++i) {
			int val = umap[i];
		}
	}
	
	return 0;
}