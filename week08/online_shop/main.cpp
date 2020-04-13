#include "OnlineStore.h"

int main() {

	// *.bin *.dat std::ios::binary
	// *.txt

	OnlineStore store;

	std::ifstream in; // stream class to read from files
	//std::ofstream out; // stream class to write on files
	//std::fstream file(std::ios::out | std::ios::in | ); 
	
	in.open("store_info.txt", std::ios::in);

	// in.bad()
	// in.fail()
	// in.eof()
	// in.good()

	// check if the file has been opened correctly
	if (!in.is_open()) {
		std::cout << "Could not open file!" << std::endl;
		return -1;
	}

	unsigned int numberOfItems;
	in >> numberOfItems;
	//file << file / stream / variable / const
	
	// in.get(&numberOfItems);
	// numberOfItems = in.get();
	// in.getline(...);

	Item currentItem;

	//while (!in.eof()) {
	//	...
	//}

	for (int i = 0; i < numberOfItems || !in.eof(); ++i) {
		in >> currentItem;
		store.add(currentItem);
	}

	in.close();
	std::cout << store << std::endl;

	system("pause");
	return 0;
}

/*
<number_of_items>
<name> <quantity> <price>
...
*/