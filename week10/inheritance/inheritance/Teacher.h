#ifndef TEACHER_H
#define TEACHER_H

#include "Person.h"

class Teacher : virtual public Person {
public:
	Teacher() {} // Teacher() : Person(), majorID(0) {}

	Teacher(const char* name, unsigned int age) :
		Person(name, age) {} // : Person()

	Teacher(const Teacher& other) :
		Person(other) {} // Person()

	Teacher& operator=(const Teacher& other) {
		if (this != &other) {
			Person::operator=(other);
		}
		return *this;
	}

	virtual ~Teacher() override {}

	void sayHello() const override {
		std::cout << "Hello, I am " << getName() << " and I belong to class Teacher.\n";
	}

private:
};

#endif