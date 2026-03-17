#include<iostream>

template<typename... Args>
void print(Args... args)
{
    ((std::cout << args << " "), ...);
}

int main()
{
    print(1, 2, 3, 4);
	// 1 2 3 4
}