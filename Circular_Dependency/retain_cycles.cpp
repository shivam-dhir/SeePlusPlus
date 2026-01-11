// Retain cycles or circular dependency keeps count of 
// strong references to an object. If all references to the object are destroyed, the memory is freed, deleted.

#include <iostream>

class Device;

class DeviceManager {
public:
	std::shared_ptr<Device> device;
	~DeviceManager() { std::cout << "DeviceManager Destroyed" << std::endl; }
}; 

class Device {
public:

	// To avoid memory, we can make the DeviceManager pointer as weak_ptr
	// Weak pointers can't be dereference normally. This is because its not necessary that the memory that the pointer points has not been deleted
	// So, a temporary shared pointer (locked) has to be created and checked if it returns a valid pointer
	// If the memory is freed, it returns null
	std::weak_ptr<DeviceManager> manager;

	//std::shared_ptr<DeviceManager> manager;
	~Device() { std::cout << "Device Destroyed" << std::endl; }
};

int main() {

	// std::make_shared creates an object on the heap and returns a std::shared_ptr
	auto mgr = std::make_shared<DeviceManager>();
	std::cout << "After make_shared: mgr.use_count() = " << mgr.use_count() << std::endl;

	auto dev = std::make_shared<Device>();
	std::cout << "After make_shared: dev.use_count() = " << dev.use_count() << std::endl;

	mgr->device = dev;
	std::cout << "After mgr->device = dev: dev.use_count() = " << dev.use_count()
		<< ", mgr.use_count() = " << mgr.use_count() << std::endl;

	dev->manager = mgr; // weak_ptr so does not affect use_count
	std::cout << "After dev->manager = mgr: dev.use_count() = " << dev.use_count()
		<< ", mgr.use_count() = " << mgr.use_count() << std::endl;

	// when a scope ends, local variables are destroyed in reverse order
	// so first dev is destroyed and then mgr
	// when dev dies, Device(count) decrments to 1 (still held by mgr -> device)
	// when mgr dies, DeviceManager(count) decrements to 1 (still held by dev -> manager) 
	// Since both DeviceManager and Device have a reference count of 1, neither of them is destroyed
	// This causes a memory leak
	// To prevent this, we can make one of the pointer as a weak_ptr, which does not increment the reference counter
	
	//decrements reference to DeviceManager. There are no more pointers to DeviceManager, which is then destroyed
	//mgr.reset(); 

	// creating a temporary shared_ptr to check if object is still alive (i.e. there is an alive shared_ptr pointing to it)
	// Since DeviceManager object (mgr) is destroyed, mgr->device is also destroyed which decrements the Device's count
	// This process is atomic, preventing race conditions

	if (auto locked = dev->manager.lock()) {
		//std::cout << "Device Manager is alive" << std::endl;
		std::cout << "Before reset: Device Manager is alive (locked.use_count() = "
			<< locked.use_count() << ")" << std::endl;
	}
	else //std::cout << "Device Manager is dead" << std::endl;
		std::cout << "Before reset: Device Manager is dead" << std::endl;

	// drop the local owning pointer to DeviceManager
	std::cout << "Calling mgr.reset()" << std::endl;
	mgr.reset(); // this will destroy the DeviceManager if no other shared_ptr owns it

	// after reset: DeviceManager should be destroyed and mgr->device (the shared_ptr) destroyed,
	// which decrements Device's use_count
	std::cout << "After mgr.reset(): dev.use_count() = " << dev.use_count()
		<< ", (mgr no longer valid)" << std::endl;

	// check weak_ptr after reset
	if (auto locked = dev->manager.lock()) {
		std::cout << "After reset: Device Manager is alive (locked.use_count() = "
			<< locked.use_count() << ")" << std::endl;
	}
	else {
		std::cout << "After reset: Device Manager is dead" << std::endl;
	}

	// end of main: dev goes out of scope -> Device destroyed (if its use_count reaches 0)

	// instead of lock(), expired() can also be used, but it is not thread safe
	
	// An operation being atomic means "All-or-Nothing", i.e. the process succeeds and returns a shared_ptr or fails and returns a null
	// Other threads can't interrupt during this process

	// After using weak_ptr, when main() ends, both destructors are called because no strong references (shared pointers) remain
	
	// When an object is destroyed, first its constructor runs and then non static members are destroyed
}