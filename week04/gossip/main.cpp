#include "Gossip.h"

void test() {
	Gossip a; // constructor
	Gossip b(a); // copy constructor
	Gossip c = b; // copy constructor

	c = a; // Assignment operator
} // Destructor

int main() {

	test();

	// optional "pause" for the console
	system("pause");

	return 0;
}
