#ifndef PLAYER_H
#define PLAYER_H

#include "id.h"
#include <cstring>
#include <fstream>

typedef unsigned int uint;

class Player {
public:
	Player() {
		id = data::getAndIncrease();
		setName("unknown");
		setAge(1);
		setPoints(0);
	}

	Player(std::string name, uint age, uint points = 0) {
		id = data::getAndIncrease();
		setName(name);
		setAge(age);
		setPoints(points);
	}

	void setName(std::string name) {
		if (name.empty()) {
			throw "Invalid value for name";
		}
		this->name = name;
	}

	void setAge(uint age) {
		this->age = age;
	}

	void setPoints(uint points) {
		this->points = points;
	}

	void addPoints(uint points) {
		this->points += points;
	}

	void saveInfo(std::string fileName) {
		std::ofstream players(fileName, std::ios::out | std::ios::app);
		if (!players.is_open()) {
			throw "Could not open file " + fileName;
		}
		players << id << " " << name << " " << age << " " << points << "\n";
		players.close();
	}

private:
	std::string name;
	uint age;
	uint points;
	uint id;
};

//side note: strcmp(file.read(posStart, posEnd), expectedStr) == 0 -> false -> file.get() until " "

#endif // !PLAYER_H
