#include <iostream>

class String {
private:
	// unsigned integer of 32 bits. _t represents a typedef.
	uint32_t m_Size = 0;
	char* m_Data = nullptr;

public:
	// using default forces compiler to build a default constructor
	// when other user-defined constructors are defined, the compiler does not generate a default constructor
	String() = default;

	String(const char* string) {
		printf("created\n");
		m_Size = strlen(string);
		m_Data = new char[m_Size];
		memcpy(m_Data, string, m_Size);
	}

	// copy constructor to avoid shallow copying of pointers, which is dangerous
	String(const String& other) {
		printf("copied\n");
		m_Size = other.m_Size;
		m_Data = new char[m_Size];
		memcpy(m_Data, other.m_Data, m_Size);
	}

	// Move constructor. noexcept means no exceptions
	// It takes in a r-value reference (a temporary)
	// For this to work, Entity must have a constructor that takes in a String r-value reference (String&&)
	String(String&& other) noexcept {

		// instead of doing a deep copy and allocating new memory on heap, we just point m_Data to the old String instance
		// and make the 'other' reference as useless/ point it to null
		printf("moved\n");
		m_Size = other.m_Size;
		m_Data = other.m_Data;


		// other now becomes obsolete, since we have already taken/stolen all of its resources
		other.m_Size = 0;
		other.m_Data = nullptr;
	}

	~String() {
		printf("destroyed\n");
		delete[] m_Data; 
	}

	void print() {
		for (int i = 0; i < m_Size; i++)
			std::cout << m_Data[i];
		std::cout << "\n";
	}
};

class Entity {

private:
	String m_Name;

public:
	// first, a String instance is created using the String(const char*) constructor which binds to name, which prints "created"
	// then m_Name is created by copying name, which then calls the copy constructor and "copied" is printed
	// After copying, the temporary String instance is destroyed, which calls the destructor
	// We need to somehow avoid this redundant copying, this is where move constructor comes in
	Entity(const String& name) : m_Name(name) {}

	// For move constructor to work, we need a Entity constructor which takes in a r-value String reference 
	//Entity(String&& name) : m_Name((String&&) name) {}
	// instead of casting to String&&, we usually do std::move(namme)

	// Does the exact same thing as above, just instead using std::move()
	Entity(const String&& name): m_Name(std::move(name)) {}

	void printName() {
		m_Name.print();
	}
};

int main() {

	// implicit construction
	// First the string instance is created in this (main) scope, and is bound to String& name.
	// Then a copy happens when the instance 'name' is copied to 'm_Name' 
	//Entity entity(String("hello"));
	//entity.printName();

	std::string str1 = "hello"; // 0x000000A8ADAFF5B8
	// This creates a deep copy of str1, which is str2
	std::string str2 = str1; // 0x000000A8ADAFF5F8

	// This MOVES/STEALS the contents from str1 into str3
	// move() converts the parameter (str1) into a temporray (r-value) and gives ownership to str3.
	// str1 is then made to point to null, basically made useless
	std::string str3 = std::move(str1);
	std::cout << "str3: " << str3 << std::endl;
	std::cout << "str1: " << str1 << std::endl;

	// Since move() just converts the object into a temporary, we could just explicitly convert it into a r-value reference
	// But this is not very safe, and could misbehave/have undefined behaviour with some types (eg: auto). std::move() is the best way to do this
	std::string str4 = (std::string&&) str3;
	
}