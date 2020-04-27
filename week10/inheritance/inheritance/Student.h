#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

class Student : virtual public Person {
public:
	Student() : majorID(0) {} // Student() : Person(), majorID(0) {}
	
	Student(const char* name, unsigned int age, unsigned int major_id) : 
		Person(name, age), majorID(major_id) {} // : Person()
	
	Student(const Student& other) : 
		Person(other), majorID(other.majorID) {} // Person()
	
	Student& operator=(const Student& other) {
		if (this != &other) {
			Person::operator=(other);
			majorID = other.majorID;
		}
		return *this;
	}
	
	virtual ~Student() override {}

	void sayHello() const override {
		std::cout << "Hello, I am " << getName() << " and I belong to class Student.\n";
	}

private:
	unsigned int majorID;
};


#endif
