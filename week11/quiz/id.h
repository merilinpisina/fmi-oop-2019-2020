#ifndef UNIQUE_ID
#define UNIQUE_ID

#include <iostream>
#include <fstream>
#include <sstream>

namespace data {
	static unsigned int id = 0;
	void initialize();
	unsigned int getAndIncrease();
	void save();
}
const unsigned int system_id = 4294967295;

#endif