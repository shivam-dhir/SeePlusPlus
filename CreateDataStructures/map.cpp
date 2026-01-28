#include <iostream>
#include <map>
#include <unordered_map>

struct Data {
	std::string name;
	int id;
};

namespace std {

	template<>
	struct hash<Data> {
		size_t operator()(const Data& key) const {
			return hash<std::string>()(key.name);
		}
	};
}

int main() {

	std::map<std::string, int> map;
	map["apple"] = 1;
	map["orange"] = 2;
	map["banana"] = 3;

	/*for (auto& [key, value] : map) {
		std::cout << key << ": " << value << std::endl;
	}*/

	std::unordered_map<std::string, int> u_map;
	u_map["apple"] = 1;
	u_map["orange"] = 2;
	u_map["banana"] = 3;

	// index operator inserts the element if not found.
	// this will not work with const maps, because they wont allow modifications
	u_map["grape"] = 4;

	// at() is used to get value of key without inserting. If key is not present, program will crash
	int val = u_map.at("apple");

	// cant use int to store result as key might not be present
	auto it = map.find("kiwi");
	if (it != map.end()) {
		int val1 = it->second;
		// use val1 as needed
	} else {
		// handle key not found case
	}

	// using structured bindings to iterate over map
	for (auto& [key, value] : u_map) {
		std::cout << key << ": " << value << std::endl;
	}

	/*std::unordered_map<Data, int> dataMap;
	dataMap[{"mumbai", 69}] = 1;
	dataMap[{"delhi", 53}] = 2;
	dataMap[{"kolkata", 48}] = 3;*/

}