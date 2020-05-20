#include "id.h"

void data::initialize() {
	if (data::id != 0) {
		return;
	}
	std::ifstream uid;
	uid.open("uid.dat", std::ios::in | std::ios::binary);
	if (!uid) {
		throw std::exception("Could not open configuration file [uid.dat]!");
	}

	std::string line;
	std::getline(uid, line);

	std::stringstream value(line);
	value.clear();
	if (!value)
	{
		throw std::exception("Could not read configuration file [uid.dat]!");
	}

	value >> data::id;
	uid.close();
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
		throw std::exception("Could not open & save configuration file [uid.dat]!");
	}
	uid << data::id;
	uid.close();
}