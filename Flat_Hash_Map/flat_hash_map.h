#pragma once

#include <functional>
#include <utility>
#include <optional>

template<typename K, typename V>
class FlatHashMap {

private:

    // 4 + 4 + 1 + 3(padding) = 12 bytes
	// Better cache locality. Extra bools can be added at the end without increasing the size of the struct.
    struct Entry {
        K key;
        V value;
        bool occupied = false;
    };

	// 1 + 3(padding) + 4 + 4 = 12 bytes
	// extra flags/data at the end of the struct increase the size of the struct.
    //struct Entry {
    //    bool occupied;
    //    K key;
    //    V value;
    //};

    Entry* table;
    size_t capacity;
    size_t size;

public:

    FlatHashMap(size_t cap = 16)
        : capacity(cap), size(0)
    {
        table = new Entry[capacity];
    }

    ~FlatHashMap()
    {
        delete[] table;
    }

    void resize() {
        size_t new_capacity = capacity * 2;
        Entry* new_table = new Entry[new_capacity];
        for (size_t i = 0; i < capacity; ++i) {
            if (table[i].occupied) {
                size_t index = std::hash<K>{}(table[i].key) % new_capacity;
                while (new_table[index].occupied) {
                    index = (index + 1) % new_capacity;
                }
                new_table[index] = std::move(table[i]);
            }
        }
        delete[] table;
        table = new_table;
		capacity = new_capacity;
    }

    void insert(const K& key, const V& value)
    {
        if (size >= capacity * 0.75) {
            resize();
        }
		size_t index = std::hash<K>{}(key) % capacity;
        while (table[index].occupied) {
            if (table[index].key == key) {
                table[index].value = value;
                return;
            }
            index = (index + 1) % capacity;
        }
        table[index] = {key, value, true};
        ++size;
	}

    V* get(const K& key) {
        size_t index = std::hash<K>{}(key) % capacity;
        while (table[index].occupied) {
            if (table[index].key == key) {
                return &table[index].value;
            }
            index = (index + 1) % capacity;
        }
		return nullptr;
    }

};