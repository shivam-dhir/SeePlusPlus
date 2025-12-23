// unique pointer is a scoped pointer. 
// unique pointers cannot be copied. This because 2 pointers might be pointing to same memory address
// when one of them is destroyed, the other is basically pointing to nothing/null

// shared pointer is also a scoped pointer
// since unique pointers cannot be copied/duplicated, shared_pointer help us with this problem
// shared pointers keep a count of every copy of the pointer. 

// weak pointer are somewhat similar to shared pointer
// the only difference is that weak pointer does not increment the count of shared pointer
// so if the original pointer and its copies are destroyed, i.e. count becomes 0, the memory and pointer are destroyed, but the weak pointer
// is still alive, but becomes a dangling pointer, as the memory it pointed to is now free

#include <iostream>
#include <memory>

class Example {

public:
	Example() {
		std::cout << "Example Constructor called" << std::endl;
	}

	~Example() {
		std::cout << "Example Destructor called" << std::endl;
	}
};

int main() {
	//std::unique_ptr<Example> example = new Example(); // implicit conversion is not allowed since
	// the constructor of unique_ptr is marked as explicit


	//std::unique_ptr<Example> example(new Example());

	// Preferred way. make_unique handles exceptions for us.
	// if the unique_ptr constructor is not able to create a pointer for us, we might be left with a 
	// dangling pointer which will cause a memory leak
	// make_unique helps avoid this
	{
		std::unique_ptr<Example> example = std::make_unique<Example>();
		std::unique_ptr<Example> copy_ptr = example; // unique pointers can't be copied
	}
	// As the above scope ends, example will go out of scope and will be automatically deleted,
	// since its a unique pointer, which is just a wrapper around a basic pointer


	// Since unique pointers can't be copied, therefore they can't be passed to a function either
	// becuase when a pointer is passed to a function, a local copy of the pointer is created.
	// To tackle this, shared pointers are used. Shared pointers use reference counting. 
	// A count of the number of copies of the pointer is tracked. When a copy is created, count is increased
	// and when a copy is deleted, count is decremented
	// When the count hits 0, the corresponding 
	// memory block in heap is freed
	std::shared_ptr<Example> shared_example(new Example());
	
	// using new with shared pointer is not allowed because, shared pointer constructor also initializes
	// the example pointer. So, first the new keyword will create a pointer, and then shared pointer constructor
	// will, which results in 2 counts of the same pointer, which is incorrect
	// make_shared_ should be used, which creates only a single instance
	//std::shared_ptr<Example> shared_example_0 = new Example();


	std::weak_ptr<Example> weak_pointer;
	{
		// original pointer
		std::shared_ptr<Example> shared_ptr = std::make_shared<Example>();

		// weak_pointer is of type weak_ptr, which does not increment the reference count 
		weak_pointer = shared_ptr;
		{
			// copy pointer
			std::shared_ptr<Example> shared_ptr_copy = shared_ptr; // copy created, and reference count will be incremented
			
		}
		//shared_ptr_copy goes out of scope and is destroyed & count is decreased by 1, but shared_ptr is still alive, so destructor is not called
		// at this point, weak
	}
	//shared_ptr goes out of scope, and all copies are destroyed, now the destructor is called
	// at this point, weak_ptr is still alive, but all shared_ptr copies have been destroyed and heap memory has been freed.
	// so, weak_pointer is a dangling pointer, which now points to nothing/null
}