// Basic gist
// L values: have some storage assigned to them and have a lifetime
// R values: temporary values which are just about to be destroyed and have no storgage assigned to them

// Rule: It is not possible to take an L-value reference from an R-value. We can only have a L-value reference from an l-value
#include <iostream>

// since i am taking in a l-value reference, r-values wouldn't be allowed as parameters
// This can be used to determine if the parameter is a temporary object/value (r-value)
void printNoRvalue(int& var) {

}

// r-values are allowed as parameters because i am taking in a const int reference, which can take a r-value
// so basically, const l-value references can accept both l-value and r-values
void printBothLANDRValue(const int& var) {

}

// Only r-values are allowed as parameters, l-values are not
void printOnlyRValue(std::string&& var) {

}

void print(std::string var) {
	std::cout << var << std::endl;
}

int main() {
	// i is an l value, 10 is an r value. 'i' is stored somewhere (stack). the value 14 is about to be destroyed
	int i = 14;

	int& ref = 7; // This is NOT allowed. As the rule above, it is not allowed to create l-value reference from r-value
	const int& constRef = 7; // this is a workaround. const int reference can be taken from an r-value
	// this is because, const confirms that the r-value won't be modified (which is dangerous)
	// and const extends the lifetime of the variable (r-value) to that of the caller(reference), so the compiler can create a temporary storage for the r-value and then assign it to the reference
	
	// first and second are L value's, whereas "Tamannah" and "Bhatia" are R-values
	std::string first = "Tamannah";
	std::string second = "Bhatia";

	// In this case, str is an L value, and the expression first + second is an R value
	// This is because the expression first + second creates a new temporary string "TamannahBhatia" which is assigned to the l value str
	std::string str = first + second;

	print(str);

	// In this case, an l-value is created (var) using an r-value(first + second)
	print(first + second);

	printNoRvalue(first + second); // not allowed since first + second creates a new temporary r-value string
}