#include "MathVector.h"


int main () {

	MathVector v1(4);
	std::cin >> v1;
	MathVector v2(v1);

	v2 *= 5;
	std::cout << v1;
	std::cout << v2;

	std::cout << std::boolalpha << (v1 || v2) << std::endl;

	
	
	system("pause");
	return 0;
}