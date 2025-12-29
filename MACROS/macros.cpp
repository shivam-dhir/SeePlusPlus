#include <iostream>

// everything with a # before it is a preprocessor directive
// macors are also preprocessor directives which are evaluated before compilation
#define print std::cout << 
// paramerized macro
#define Log(x) std::cout << x << std::endl;

// macros cam also be used for conditional compilation
// we can include or exclude parts of code based on certain conditions

#define DEBUG

#ifdef DEBUG
#define DebugLog(x) std::cout << "DEBUG: " << x << std::endl;
#elif defined(RELEASE)
#define DebugLog(x) std::cout << "RELEASE: " << x
#endif

// I have defined PR_DEBUG in properties under pre-processor
#if PR_DEBUG == 1
#define programLog(x) std::cout << "PR_DEBUG isACTIVE: " << x << std::endl
#else 
#define programLog(x) std::cout << "PR_DEBUG INACTIVE: " << x << std::endl  
#endif

// we can also diable blocks of code using macros
// we can use conditions which result in true or false to allow/block the subsequent block
#if 0
#define doSomething 69
#endif

// #ifdef -> checks if macro is defined
// #ifndef -> checks if macro is not defined
// #else/elif -> alternative code if #ifdef condition is false
// #endif -> #ifdef must be closed with #endif

// '\' character allows us to write mutiple line macros
#define MAIN int main() \
{\
	std::cout << "Hello" << std::endl;\
}

// MAIN

int main() {

	print "shibum\n";
	Log("macros");

	DebugLog("version 1.2");

	programLog("1.5.2");

	//std::cout << doSomething << std::endl;
}