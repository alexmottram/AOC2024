#include  <iostream>
#include "utils/utils.h"


int main() {
	std::cout << "Hello world!" << std::endl;
	int n = 10;
	std::cout << "Factorial of: " << n << " is: " << utils::factorial(n) << std::endl;
	return 0;
}