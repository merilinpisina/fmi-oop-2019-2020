#include "id.h"

void data::initialize() {
	if (data::id != 0) {
		return;
	}
	std::ifstream uid;
	// File should be config.dat
	uid.open("uid.dat", std::ios::in | std::ios::binary);
	if (!uid) {
		std::cout << "Not opened\n";
		//handle it
	}
	else {
		std::string line;
		std::getline(uid, line);

		std::stringstream value(line);
		value.clear();
		if (!value)
		{
			std::cout << "Not opened\n";
		}

		value >> data::id;
		uid.close();
	}
}

unsigned int data::getAndIncrease() {
	//return (data::id == system_id ? ++data::id : data::id++);
	data::save();
	return data::id++;
}

void data::save() {
	std::ofstream uid;
	uid.open("uid.dat", std::ios::out | std::ios::binary | std::ios::trunc);
	if (!uid) {
		throw("Could not open uid.dat!");
	}
	else {
		uid << data::id;
		uid.close();
	}
}
