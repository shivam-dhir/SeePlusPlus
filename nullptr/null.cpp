#include <iostream>

class Entity {
public:
	Entity() = default;
private:
	Entity* m_Parent;
	std::string m_Name;
public:

	const std::string& GetName() const { return m_Name; }
	virtual void printType() {
		std::cout << "Entity" << std::endl;
	}

	static void printStaticType() {
		std::cout << "Static Entity" << std::endl;
	}
};

// in C, there are no classes. There are only structs and functions.
// below is the C code for the above class

struct Entity_C {
	// constructor
	// there are no constructors in C, so we have to create a function to initialize the struct
	struct Entity_C* m_Parent;
	std::string m_Name;
};

// functions are not members of structs in C, so we have to pass the struct as a parameter to the function

void printEntityName(struct Entity_C* entity) {
	if (entity != NULL) {
		printf("Entity Name: %s\n", entity->m_Name);
	}
}

// a pointer to the struct is sent as the first parameter to the function, which can be considered as the 'this' pointer in C++, and access the members of the struct using the pointer.
// this is similar to how non-static member functions in C++ work.
// this is exactly what happens under the hood in C++ for non-static member functions.
const std::string GetEntityName(const struct Entity_C* self) {
		return self->m_Name;
}

// since this is static function, there is no 'this' pointer involved.
// and since there is no 'this' pointer, this function can't access any member variables of the struct.
void printStaticEntityType() {
	std::cout << "Static Entity" << std::endl;
}

int main() {

	Entity* e = nullptr;
	// this still works because we are not accessing any member variables, and e is never dereferenced. 
	// if 'e' accessed other class members or methods that do, it would lead to undefined behavior.
	//e->printType(); // Undefined Behavior: Dereferencing a null pointer
	
	// when calling a non-static member function, the compiler implicitly passes the 'this' pointer to the function.
	// when calling a static member function, there is no 'this' pointer involved.

	// when calling a virtual function, the compiler uses the vtable to resolve the function call at runtime.
	// to access the vtable, the compiler dereferences the 'this' pointer to get the vtable pointer.
	// so, if we pass in a null pointer as 'this', dereferencing it to access the vtable leads to undefined behavior.
	
	//std::cout << e->GetName() << std::endl; // Undefined Behavior: Dereferencing a null pointer
	

	// lets check the offset of the members of Entity_C struct
	// offsetof is a macro defined in <cstddef> header file
	std::cout << "Offset of m_Parent in Entity_C: " << offsetof(Entity_C, m_Parent) << " bytes" << std::endl;
	std::cout << "Offset of m_Name in Entity_C: " << offsetof(Entity_C, m_Name) << " bytes" << std::endl;

	// implementing offsetof manually
	uint64_t name_offset = (uint64_t)& (((Entity_C*)0)->m_Name);
	uint64_t parent_offset = (uint64_t) & (((Entity_C*)0)->m_Parent);

	std::cout << "Manual Offset of m_Parent in Entity_C: " << parent_offset << " bytes" << std::endl;
	std::cout << "Manual Offset of m_Name in Entity_C: " << name_offset << " bytes" << std::endl;
	
	// understanding the manual offset calculation
	// 1. We cast the null pointer (0) to a pointer of type Entity_C*
	// 2. We access the member variable using the pointer (we are not reading it's value)
	// 3. We take the address of the member variable (we just took the address)
	// 4. We cast the address to a uint64_t
	// 5. we get the offset of the member variable from the start of the struct, which we have defined as 0, so we get the offset relative to 0
	// 6. if it was allocated in memory, the address would be the base address + offset

	return 0;
}