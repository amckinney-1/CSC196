#include "Helper.h"
#include "Dynamic.h"
#include <iostream>

int main()
{
	std::cout << "Hello World\n";

	std::cout << help::sqr(5) << std::endl;

	dyn::point p1{ 10, 10 };
	dyn::point p2{ 10, 10 };
	dyn::point p3 = p1 + p2;

	std::cout << p3.x << " " << p3.y << std::endl;

	system("pause");
}