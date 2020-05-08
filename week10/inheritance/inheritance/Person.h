#ifndef PERSON_H
#define PERSON_H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <cassert>

class Person {
public:
	Person(): age(0), name(nullptr){}
	Person(const char* nname, unsigned int age) : age(age), name(nullptr) {
		assert(nname != nullptr);
		this->name = new (std::nothrow) char[strlen(nname) + 1];
		if (!this->name) {
			std::cout << "Problem allocating memory for Person::name.\n";
			return;
		}
		strcpy(this->name, nname);
	}
	Person(const Person& other) {
		this->age = other.age;
		this->name = new(std::nothrow) char[strlen(other.name) + 1];
		if (!this->name) {
			std::cout << "Problem allocating memory for Person::name.\n";
			return;
		}
		strcpy(this->name, other.name);
	}
	Person& operator= (const Person& other) {
		if (this != &other) {
			destroy();
			this->age = other.age;
			this->name = new(std::nothrow) char[strlen(other.name) + 1];
			if (!this->name) {
				std::cout << "Problem allocating memory for Person::name.\n";
				return *this;
			}
			strcpy(this->name, other.name);
		}
		return *this;
	}
	virtual ~Person() {
		destroy();
	}

	unsigned int getAge()const {
		return age;
	}

	const char* getName()const {
		return name;
	}

	virtual void sayHello()const {
		std::cout << "Hello, I am " << name << " and I belong to class Person.\n";
	}

	// friend operator>>

private:
	unsigned int age;
	char* name;

	void destroy() {
		age = 0;
		delete[]name;
		name = nullptr;
	}
};


#endif